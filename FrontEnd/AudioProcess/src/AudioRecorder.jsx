import React, { useState, useEffect, useRef } from "react";
import axios from "axios";

const AudioRecorder = () => {
  const [isRecording, setIsRecording] = useState(false);
  const [audioUrl, setAudioUrl] = useState(null);
  const [trimmedAudioUrl, setTrimmedAudioUrl] = useState(null);
  const [audioBlob, setAudioBlob] = useState(null);
  const [fileName, setFileName] = useState(null);
  const [mediaRecorder, setMediaRecorder] = useState(null);
  const [error, setError] = useState("");
  const [isUploading, setIsUploading] = useState(false);
  const [isFetching, setIsFetching] = useState(false);
  const [isPlaying, setIsPlaying] = useState(false);
  const [currentTime, setCurrentTime] = useState(0);
  const [duration, setDuration] = useState(0);
  const audioChunksRef = useRef([]);
  const audioRef = useRef(null);
  const trimmedAudioRef = useRef(null);
const [trimmedCurrentTime, setTrimmedCurrentTime] = useState(0);
const [trimmedDuration, setTrimmedDuration] = useState(0);
const [isTrimmedPlaying, setIsTrimmedPlaying] = useState(false);

const handleTrimmedPlayPause = () => {
  if (isTrimmedPlaying) {
    trimmedAudioRef.current.pause();
  } else {
    trimmedAudioRef.current.play();
  }
  setIsTrimmedPlaying(!isTrimmedPlaying);
};

const handleTrimmedTimeUpdate = () => {
  setTrimmedCurrentTime(trimmedAudioRef.current.currentTime);
};

const handleTrimmedSeek = (e) => {
  const newTime = e.target.value;
  trimmedAudioRef.current.currentTime = newTime;
  setTrimmedCurrentTime(newTime);
};

  useEffect(() => {
    let streamRef;
    navigator.mediaDevices
      .getUserMedia({ audio: true })
      .then((stream) => {
        streamRef = stream;
        const recorder = new MediaRecorder(stream, { mimeType: "audio/webm" });

        recorder.ondataavailable = (event) => {
          if (event.data.size > 0) {
            audioChunksRef.current.push(event.data);
          }
        };

        recorder.onstop = () => {
          if (audioChunksRef.current.length > 0) {
            const completeBlob = new Blob(audioChunksRef.current, { type: "audio/webm" });
            const completeUrl = URL.createObjectURL(completeBlob);

            setAudioUrl(completeUrl);
            setAudioBlob(completeBlob);
          }
          audioChunksRef.current = [];
        };

        setMediaRecorder(recorder);
      })
      .catch((err) => {
        console.error("Error accessing microphone:", err);
        setError("Microphone access denied. Please enable microphone permissions.");
      });

    return () => {
      if (streamRef) {
        streamRef.getTracks().forEach((track) => track.stop());
      }
    };
  }, []);

  const startRecording = () => {
    if (mediaRecorder) {
      audioChunksRef.current = [];
      mediaRecorder.start();
      setIsRecording(true);
    }
  };

  const stopRecording = () => {
    if (mediaRecorder && isRecording) {
      mediaRecorder.stop();
      setIsRecording(false);
    }
  };

  const deleteAudio = () => {
    setAudioUrl(null);
    setTrimmedAudioUrl(null);
    setAudioBlob(null);
    setFileName(null);
  };

  const sendAudioToBackend = async () => {
    if (!audioBlob) {
      alert("No recorded audio to send.");
      return;
    }

    setIsUploading(true);
    const formData = new FormData();
    const uniqueFileName = `audio_${Date.now()}.webm`;
    formData.append("file", audioBlob, uniqueFileName);

    try {
      const response = await axios.post("http://localhost:8080/audio/upload", formData, {
        headers: { "Content-Type": "multipart/form-data" },
      });

      console.log("Audio uploaded successfully:", response.data);
      setFileName(uniqueFileName);
      alert("Audio uploaded successfully!");
    } catch (error) {
      console.error("Error uploading audio:", error);
      alert("Failed to upload audio.");
    } finally {
      setIsUploading(false);
    }
  };

  const fetchTrimmedAudio = async () => {
    if (!fileName) {
      alert("No processed file to fetch.");
      return;
    }

    setIsFetching(true);
    try {
      const trimmedFileName = fileName.replace(".webm", "_trimmed.webm");
      const response = await axios.get(`http://localhost:8080/audio/trimmed/${trimmedFileName}`, {
        responseType: "blob",
      });

      const url = URL.createObjectURL(response.data);
      setTrimmedAudioUrl(url);
      alert("Processed audio ready for playback!");
    } catch (error) {
      console.error("Error fetching trimmed audio:", error);
      alert("Failed to fetch trimmed audio.");
    } finally {
      setIsFetching(false);
    }
  };

  const handlePlayPause = () => {
    if (audioRef.current.paused) {
      audioRef.current.play();
      setIsPlaying(true);
    } else {
      audioRef.current.pause();
      setIsPlaying(false);
    }
  };

  const handleTimeUpdate = () => {
    setCurrentTime(audioRef.current.currentTime);
    setDuration(audioRef.current.duration);
  };

  const handleSeek = (e) => {
    audioRef.current.currentTime = e.target.value;
    setCurrentTime(e.target.value);
  };

  return (
    <div className="flex flex-col items-center justify-center min-h-screen w-full bg-gradient-to-r from-gray-900 via-gray-800 to-gray-900 text-white p-6">
      <h1 className="text-4xl font-bold mb-8 bg-clip-text text-transparent bg-gradient-to-r from-blue-400 to-purple-500">
        Voice Canvas
      </h1>
      {error && <p className="text-red-500 mb-4 text-sm">{error}</p>}

      <div className="flex space-x-3 mb-6">
        <button
          onClick={startRecording}
          className={`px-4 py-2 text-sm rounded-lg backdrop-blur-sm bg-white/10 border border-white/20 hover:bg-white/20 transition-all ${
            isRecording ? "cursor-not-allowed opacity-50" : ""
          }`}
          disabled={isRecording}
        >
          {isRecording ? "Recording..." : "Record"}
        </button>
        <button
          onClick={stopRecording}
          className={`px-4 py-2 text-sm rounded-lg backdrop-blur-sm bg-white/10 border border-white/20 hover:bg-white/20 transition-all ${
            !isRecording ? "cursor-not-allowed opacity-50" : ""
          }`}
          disabled={!isRecording}
        >
          Stop
        </button>
      </div>

      {audioUrl && (
        <div className="w-full max-w-2xl backdrop-blur-sm bg-white/10 border border-white/20 rounded-lg p-6">
          <h2 className="text-xl font-semibold mb-4 bg-clip-text text-transparent bg-gradient-to-r from-blue-400 to-purple-500">
            Original Capture
          </h2>
          <div className="flex flex-col space-y-4">
            <audio
              ref={audioRef}
              src={audioUrl}
              onTimeUpdate={handleTimeUpdate}
              onLoadedMetadata={() => setDuration(audioRef.current.duration)}
              className="hidden"
            />
            <div className="flex items-center space-x-4">
              <button
                onClick={handlePlayPause}
                className="p-2 rounded-full backdrop-blur-sm bg-white/10 border border-white/20 hover:bg-white/20 transition-all"
              >
                {isPlaying ? (
                  <svg
                    xmlns="http://www.w3.org/2000/svg"
                    className="h-6 w-6"
                    fill="none"
                    viewBox="0 0 24 24"
                    stroke="currentColor"
                  >
                    <path
                      strokeLinecap="round"
                      strokeLinejoin="round"
                      strokeWidth={2}
                      d="M10 9v6m4-6v6m7-3a9 9 0 11-18 0 9 9 0 0118 0z"
                    />
                  </svg>
                ) : (
                  <svg
                    xmlns="http://www.w3.org/2000/svg"
                    className="h-6 w-6"
                    fill="none"
                    viewBox="0 0 24 24"
                    stroke="currentColor"
                  >
                    <path
                      strokeLinecap="round"
                      strokeLinejoin="round"
                      strokeWidth={2}
                      d="M14.752 11.168l-3.197-2.132A1 1 0 0010 9.87v4.263a1 1 0 001.555.832l3.197-2.132a1 1 0 000-1.664z"
                    />
                    <path
                      strokeLinecap="round"
                      strokeLinejoin="round"
                      strokeWidth={2}
                      d="M21 12a9 9 0 11-18 0 9 9 0 0118 0z"
                    />
                  </svg>
                )}
              </button>
              <input
                type="range"
                min="0"
                max={duration || 0}
                value={currentTime}
                onChange={handleSeek}
                className="w-full h-2 bg-white/20 rounded-full appearance-none cursor-pointer"
              />
              <span className="text-sm">
                {`${Math.floor(currentTime / 60)}:${Math.floor(currentTime % 60)
                  .toString()
                  .padStart(2, "0")}`}
              </span>
            </div>
          </div>
          <div className="flex space-x-3 mt-6">
            <button
              onClick={deleteAudio}
              className="px-4 py-2 text-sm rounded-lg backdrop-blur-sm bg-white/10 border border-white/20 hover:bg-white/20 transition-all"
            >
              Discard
            </button>
            <button
              onClick={sendAudioToBackend}
              className={`px-4 py-2 text-sm rounded-lg backdrop-blur-sm bg-white/10 border border-white/20 hover:bg-white/20 transition-all ${
                isUploading ? "cursor-not-allowed opacity-50" : ""
              }`}
              disabled={isUploading}
            >
              {isUploading ? "Sending..." : "Transmit"}
            </button>
          </div>
          {fileName && (
            <button
              onClick={fetchTrimmedAudio}
              className={`px-4 py-2 mt-6 text-sm rounded-lg backdrop-blur-sm bg-white/10 border border-white/20 hover:bg-white/20 transition-all ${
                isFetching ? "cursor-not-allowed opacity-50" : ""
              }`}
              disabled={isFetching}
            >
              {isFetching ? "Retrieving..." : "Encrypt"}
            </button>
          )}
        {trimmedAudioUrl && (
  <div className="w-full max-w-2xl backdrop-blur-sm bg-white/10 border border-white/20 rounded-lg p-6 mt-6">
    <h2 className="text-xl font-semibold mb-4 bg-clip-text text-transparent bg-gradient-to-r from-blue-400 to-purple-500">
      Encrypted Audio
    </h2>
    <div className="flex flex-col space-y-4">
      <audio
        ref={trimmedAudioRef}
        src={trimmedAudioUrl}
        onTimeUpdate={handleTrimmedTimeUpdate}
        onLoadedMetadata={() => setTrimmedDuration(trimmedAudioRef.current.duration)}
        className="hidden"
      />
      <div className="flex items-center space-x-4">
        <button
          onClick={handleTrimmedPlayPause}
          className="p-2 rounded-full backdrop-blur-sm bg-white/10 border border-white/20 hover:bg-white/20 transition-all"
        >
          {isTrimmedPlaying ? (
            <svg
              xmlns="http://www.w3.org/2000/svg"
              className="h-6 w-6"
              fill="none"
              viewBox="0 0 24 24"
              stroke="currentColor"
            >
              <path
                strokeLinecap="round"
                strokeLinejoin="round"
                strokeWidth={2}
                d="M10 9v6m4-6v6m7-3a9 9 0 11-18 0 9 9 0 0118 0z"
              />
            </svg>
          ) : (
            <svg
              xmlns="http://www.w3.org/2000/svg"
              className="h-6 w-6"
              fill="none"
              viewBox="0 0 24 24"
              stroke="currentColor"
            >
              <path
                strokeLinecap="round"
                strokeLinejoin="round"
                strokeWidth={2}
                d="M14.752 11.168l-3.197-2.132A1 1 0 0010 9.87v4.263a1 1 0 001.555.832l3.197-2.132a1 1 0 000-1.664z"
              />
            </svg>
          )}
        </button>
        <input
          type="range"
          min="0"
          max={trimmedDuration}
          value={trimmedCurrentTime}
          onChange={handleTrimmedSeek}
          className="w-full accent-blue-500"
        />
        <span className="text-sm">{Math.floor(trimmedCurrentTime)} / {Math.floor(trimmedDuration)} sec</span>
      </div>
    </div>
  </div>
)}


        </div>
      )}
    </div>
  );
};

export default AudioRecorder;