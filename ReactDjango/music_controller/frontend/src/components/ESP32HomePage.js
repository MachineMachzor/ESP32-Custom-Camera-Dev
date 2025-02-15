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
      <Grid container spacing={3}>
        <Grid item xs={12} align="center">
          <Typography variant="h3" compact="h3">
            ESP32Cam
          </Typography>
        </Grid>
        {/* <Grid item xs={12} align="center">
          <ButtonGroup disableElevation variant="contained" color="primary">
            <Button color="primary" to="/join" component={Link}>
              Join a Room
            </Button>
            <Button color="secondary" to="/create" component={Link}>
              Create a Room
            </Button>
          </ButtonGroup>
        </Grid> */}
      </Grid>
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
