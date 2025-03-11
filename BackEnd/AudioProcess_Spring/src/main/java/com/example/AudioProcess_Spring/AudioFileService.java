package com.example.AudioProcess_Spring;

import org.springframework.stereotype.Service;
import org.springframework.web.multipart.MultipartFile;

import java.io.*;
import java.net.Socket;

@Service
public class AudioFileService {

    private static final String UPLOAD_DIR = "C:/uploads/";
    private static final String FPGA_IP = "191.168.10.1";
    private static final int FPGA_PORT = 5000 ;
    private final Fpga fpga;

    public AudioFileService(Fpga fpga) {
        this.fpga = fpga;
    }

    public String processAudio(MultipartFile webmFile) {
        try {
            File uploadDir = new File(UPLOAD_DIR);
            if (!uploadDir.exists() && !uploadDir.mkdirs()) {
                return "Error creating upload directory!";
            }

            // Extract base name without extension
            String originalFilename = webmFile.getOriginalFilename();
            if (originalFilename == null || originalFilename.isEmpty()) {
                return "Invalid file name!";
            }
            String baseName = originalFilename.substring(0, originalFilename.lastIndexOf('.'));

            File originalFile = new File(UPLOAD_DIR, originalFilename);
            webmFile.transferTo(originalFile);

            // Fix WebM timestamps using FFmpeg
            File fixedWebMFile = new File(UPLOAD_DIR, baseName + "_fixed.webm");
            if (!fixWebMTimestamps(originalFile, fixedWebMFile)) {
                return "Error fixing WebM timestamps!";
            }

            // Convert fixed WebM to WAV
            File wavFile = new File(UPLOAD_DIR, baseName + ".wav");
            if (!convertWebMToWav(fixedWebMFile, wavFile)) {
                return "Error converting WebM to WAV!";
            }

            double duration = getAudioDuration(wavFile);
            if (duration <= 0) {
                return "Error retrieving WAV duration!";
            }
            System.out.println("Converted WAV File Duration: " + duration + " seconds");

            File noiseFile = new File(UPLOAD_DIR, "noise.wav");
            File trimmedWebMFile = new File(UPLOAD_DIR, baseName + "_trimmed.webm");

            if (noiseFile.exists()) {
                if (trimNoiseFile(noiseFile, trimmedWebMFile, duration)) {
                    return baseName + "_trimmed.webm"; // Return WebM file name
                } else {
                    return "Error trimming noise file!";
                }
            } else {
                return "Noise file not found!";
            }
        } catch (Exception e) {
            e.printStackTrace();
            return "Error processing audio file: " + e.getMessage();
        }
    }

    private boolean fixWebMTimestamps(File inputWebM, File outputWebM) throws IOException {
        String command = String.format("ffmpeg -y -fflags +genpts -i \"%s\" -c copy \"%s\"",
                inputWebM.getAbsolutePath(), outputWebM.getAbsolutePath());
        return executeFFmpegCommand(command);
    }

    private boolean convertWebMToWav(File webmFile, File wavFile) throws IOException {
        File oggFile = new File(UPLOAD_DIR, "temp.ogg");
        String command1 = String.format("ffmpeg -y -i \"%s\" -c:a libopus \"%s\"",
                webmFile.getAbsolutePath(), oggFile.getAbsolutePath());
        if (!executeFFmpegCommand(command1)) {
            return false;
        }

        String command2 = String.format("ffmpeg -y -i \"%s\" -c:a pcm_s16le -ar 48000 -ac 1 \"%s\"",
                oggFile.getAbsolutePath(), wavFile.getAbsolutePath());
        System.out.println("🎶🎶Webm to PCM is Converted Successfully");
        return executeFFmpegCommand(command2);
    }

    private double getAudioDuration(File inputFile) throws IOException {
        String command = String.format("ffprobe -i \"%s\" -show_entries format=duration -v quiet -of csv=p=0",
                inputFile.getAbsolutePath());

        Process process = new ProcessBuilder("cmd.exe", "/c", command).redirectErrorStream(true).start();
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()))) {
            String line = reader.readLine();
            if (line == null || line.trim().isEmpty()) {
                return 0.0;
            }
            return Double.parseDouble(line.trim());
        } catch (NumberFormatException e) {
            return 0.0;
        }
    }

    private void sendToFPGA() {
        try {
            System.out.println("Simulating sending file to FPGA...");
            Thread.sleep(2000);
            System.out.println("FPGA processing in progress...");
            Thread.sleep(3000);
            fpga.message2();
            fpga.message1();
            fpga.message3();
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
    }

    private boolean trimNoiseFile(File noiseFile, File outputWebMFile, double duration) throws IOException {
        if (duration <= 0) {
            return false;
        }

        // Temporary trimmed WAV file
        File trimmedWavFile = new File(UPLOAD_DIR, "trimmed_temp.wav");
        String trimCommand = String.format(
                "ffmpeg -y -i \"%s\" -t %.2f -c copy \"%s\"",
                noiseFile.getAbsolutePath(), duration, trimmedWavFile.getAbsolutePath()
        );

        if (!executeFFmpegCommand(trimCommand)) {
            return false;
        }

        // Step 2: Convert the trimmed WAV file to WebM format
        String convertCommand = String.format(
                "ffmpeg -y -i \"%s\" -c:a libopus \"%s\"",
                trimmedWavFile.getAbsolutePath(), outputWebMFile.getAbsolutePath()
        );

        sendToFPGA();  // Simulate FPGA processing

        return executeFFmpegCommand(convertCommand);
    }

    private boolean executeFFmpegCommand(String command) throws IOException {
        Process process = new ProcessBuilder("cmd.exe", "/c", command).redirectErrorStream(true).start();
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()))) {
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
        }
        try {
            return process.waitFor() == 0;
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
            return false;
        }

    }
    private void sendPcmToFpga(String pcmFilePath) throws IOException {

        try (Socket socket = new Socket(FPGA_IP, FPGA_PORT);
             OutputStream outputStream = socket.getOutputStream();
             FileInputStream fileInputStream = new FileInputStream(new File(pcmFilePath))) {

            byte[] buffer = new byte[1024];
            int bytesRead;
            int totalBytesSent = 0;
            int packetCount = 0;

            while ((bytesRead = fileInputStream.read(buffer)) != -1) {
                outputStream.write(buffer, 0, bytesRead);
                totalBytesSent += bytesRead;
                packetCount++;
                System.out.println("📤 Sent packet " + packetCount + " (" + bytesRead + " bytes)");
            }

            // Send end-of-transmission signal
            outputStream.flush();
            System.out.println("✅ End-of-transmission signal sent.");
            System.out.println("📊 Total bytes sent: " + totalBytesSent + " in " + packetCount + " packets");

        } catch (IOException e) {
            System.err.println("❌ Error sending PCM to FPGA over TCP: " + e.getMessage());
            throw new IOException("TCP Transmission failed.");
        }

        System.out.println("🔌 TCP socket closed.");
    }
}
