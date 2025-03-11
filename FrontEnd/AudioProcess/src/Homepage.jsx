import React from "react";
import { useNavigate } from "react-router-dom";
import { motion } from "framer-motion";

const HomePage = () => {
    const navigate = useNavigate();

    return (
        <div className="flex flex-col items-center justify-center h-screen bg-gradient-to-r from-gray-900 via-gray-800 to-gray-900 text-white text-center p-6">
            {/* Animated Title */}
            <motion.h1 
                className="text-6xl md:text-7xl lg:text-8xl font-extrabold mb-6 p-9 bg-white text-transparent bg-clip-text drop-shadow-lg"
                initial={{ opacity: 0, y: -30 }} 
                animate={{ opacity: 1, y: 0 }} 
                transition={{ duration: 1 }}
            >
                Secure Audio Encryption System
            </motion.h1>

            {/* Subheading */}
            <motion.p 
                className="text-lg md:text-xl lg:text-2xl italic mb-6 max-w-2xl mx-auto font-light text-gray-300"
                initial={{ opacity: 0, x: -40 }}
                animate={{ opacity: 1, x: 0 }}
                transition={{ duration: 1, delay: 0.5 }}
            >
                Protecting your speech with cutting-edge encryption.
            </motion.p>

            {/* Animated Quote Cards */}
            <div className="grid grid-cols-1 md:grid-cols-2 gap-6 w-full max-w-4xl">
                <motion.div 
                    className="p-6 bg-gray-800 bg-opacity-50 rounded-lg shadow-xl backdrop-blur-lg"
                    initial={{ opacity: 0, y: 20 }}
                    animate={{ opacity: 1, y: 0 }}
                    transition={{ duration: 1, delay: 0.8 }}
                >
                    <p className="text-lg font-medium">"Without encryption, we have no way to protect our speech."</p>
                    <span className="block mt-2 text-sm text-gray-400">– Edward Snowden</span>
                </motion.div>
                <motion.div 
                    className="p-6 bg-gray-800 bg-opacity-50 rounded-lg shadow-xl backdrop-blur-lg"
                    initial={{ opacity: 0, y: 20 }}
                    animate={{ opacity: 1, y: 0 }}
                    transition={{ duration: 1, delay: 1 }}
                >
                    <p className="text-lg font-medium">"Encryption is the protector of privacy in the digital world."</p>
                    <span className="block mt-2 text-sm text-gray-400">– Bruce Schneier</span>
                </motion.div>
            </div>

            {/* Animated Start Button */}
            <motion.button
                onClick={() => navigate("/record")}
                className="mt-8 px-8 py-4 bg-blue-600 text-white text-xl font-semibold rounded-lg shadow-lg transition transform hover:scale-105 hover:shadow-xl focus:outline-none focus:ring-4 focus:ring-blue-500/50"
                initial={{ scale: 0.8 }}
                animate={{ scale: 1 }}
                whileHover={{ scale: 1.1 }}
                whileTap={{ scale: 0.95 }}
                transition={{ duration: 0.3, type: "spring", stiffness: 100 }}
            >
                Get Started
            </motion.button>
        </div>
    );
};

export default HomePage;