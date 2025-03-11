import { useState } from 'react'
import { Router, Routes,Route, BrowserRouter } from 'react-router-dom'
import HomePage from './Homepage'
import AudioRecorder from './AudioRecorder'
function App() {

  return (
    <>
      <BrowserRouter>
        <Routes>
        <Route path="/" element={<HomePage/>} />
        <Route path="/record" element={<AudioRecorder />} />
        </Routes>
      </BrowserRouter>
    </>
  )
}

export default App
