import React, { Component } from "react";
import { Button, Grid, Typography, ButtonGroup } from "@mui/material";
// import { makeStyles } from '@mui/styles';

import { useNavigate, Link } from "react-router-dom";

// For the router
import { BrowserRouter as Router, Routes, Route } from "react-router-dom";

const HomePage = () => {
  // const navigate = useNavigate();

  const renderHomePage = () => {
    return (
      <div>
        <div item xs={12} align="center">
          <Typography variant="h3" compact="h3">
            ESP32Cam
          </Typography>
        </div>
        {/* <div item xs={12} align="center">
          <ButtonGroup disableElevation variant="contained" color="primary">
            <Button color="primary" to="/join" component={Link}>
              Join a Room
            </Button>
            <Button color="secondary" to="/create" component={Link}>
              Create a Room
            </Button>
          </ButtonGroup>
        </div> */}
        <section id="buttons">
          <button id="get-still">Get Still</button>
          <button id="toggle-stream">Start Stream</button>
        </section>
        <figure>
          <div id="stream-container" className="image-container hidden">
            <a
              id="save-still"
              href="#"
              className="button save"
              download="capture.jpg"
            >
              Save
            </a>
            <div className="close" id="close-stream">
              ×
            </div>
            <img
              id="stream"
              src="http://127.0.0.1:5000/video_feed"
              alt="Video Stream"
            />
            <img id="stream" src="" />
            {/* crossorigin */}
          </div>
        </figure>
      </div>
    );
  };

  return (
    <Router>
      <Routes>
        <Route path="/" element={renderHomePage()} />
        {/* <Route path="/join" element={<RoomJoinPage />} />
        <Route path="/create" element={<CreateRoomPage />} />
        <Route path="/room/:roomCode" element={<Room />} /> */}
        {/* :roomCode is a variable. This by default passes roomCode as "matched", which is just a param for how it got there, and we can use this to get the room */}
      </Routes>
    </Router>
  );
};

export default HomePage;
