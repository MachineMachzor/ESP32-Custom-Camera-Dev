import React, { Component } from "react";
import HomePage from "./HomePage";
import ESP32HomePage from "./ESP32HomePage";
import RoomJoinPage from "./RoomJoinPage";
import CreateRoomPage from "./CreateRoomPage";

import { render } from "react-dom";
import ReactDOM from "react-dom";

export default class App extends Component {
  constructor(props) {
    super(props);
  }

  render() {
    return (
      <div className="center">
        <ESP32HomePage />
      </div>
    );
  }
}

const appDiv = document.getElementById("app");
// render(<App />, appDiv);
ReactDOM.render(<App />, appDiv);
// if (appDiv) {
//   render(<App />, appDiv);
// } else {
//   console.error("App div not found!");
// }
// render(<App />, appDiv);

// Run code like:
// 1. python .\music_controller\manage.py runserver
// 2. cd .\music_controller\frontend\
// 3. npm run dev
