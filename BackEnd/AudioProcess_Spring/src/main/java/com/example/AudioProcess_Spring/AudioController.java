package com.example.AudioProcess_Spring;
import org.springframework.core.io.Resource;
import org.springframework.core.io.UrlResource;
import org.springframework.http.HttpHeaders;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;

import java.nio.file.Path;
import java.nio.file.Paths;

@RestController
@RequestMapping("/audio")
@CrossOrigin(origins = "http://localhost:5173/")
public class AudioController {

    private final AudioFileService audioProcessingService;
    private static final String NOISE_DIRECTORY = "C:/uploads/"; // Change this to your actual directory

    public AudioController(AudioFileService audioProcessingService) {
        this.audioProcessingService = audioProcessingService;
    }

    // Upload and process audio
    @PostMapping("/upload")
    public ResponseEntity<String> uploadAudio(@RequestParam("file") MultipartFile webmFile) {
        String response = audioProcessingService.processAudio(webmFile);
        return ResponseEntity.ok(response);
    }

    // Retrieve the trimmed noise file
    @GetMapping("/trimmed/{fileName}")
    public ResponseEntity<Resource> getTrimmedAudio(@PathVariable String fileName) {
        try {
            Path filePath = Paths.get(NOISE_DIRECTORY).resolve(fileName).normalize();
            Resource resource = new UrlResource(filePath.toUri());

            if (resource.exists() && resource.isReadable()) {
                return ResponseEntity.ok()
                        .contentType(MediaType.APPLICATION_OCTET_STREAM)
                        .header(HttpHeaders.CONTENT_DISPOSITION, "attachment; filename=\"" + fileName + "\"")
                        .body(resource);
            } else {
                return ResponseEntity.notFound().build();
            }
        } catch (Exception e) {
            return ResponseEntity.internalServerError().build();
        }
    }
}
