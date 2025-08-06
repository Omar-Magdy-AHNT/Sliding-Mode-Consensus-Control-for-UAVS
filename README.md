# Sliding Mode Consensus Control For UAVs  

### Description  
This project utilizes Hybrid Automata and Sliding Mode Control to tackle UAV consensus control. Simulations were conducted in MATLAB and ArduPilot-Gazebo for proof of concept.  

### Report  
For a detailed explanation of the methodology, simulations, and results, please refer to the [report](/Report.pdf) available in this repository. It includes in-depth discussions on control strategies, implementation details, and performance evaluation.  

### How To Run  

#### MATLAB  
- [Consensus Control For Particles](/Simulation%20Matlab/Consensus%20control%20with%20Particles/Particle_Formation.slx)  
- [Centralized Consensus Control for UAVs](/Simulation%20Matlab/Consensus%20control%20with%20SMC%20low%20Level%20controller/Formation.slx)  

#### ArduPilot-Gazebo  
1. Run Software in the Loop for the **[Leader](/Simulation%20Gazebo/sitl1.sh)** and **[Follower](/Simulation%20Gazebo/sitl2.sh)**  
2. Launch the **[APM Configuration](/Simulation%20Gazebo/apmx.launch)**  
3. Start the **[Gazebo Environment](/Simulation%20Gazebo/gaz2.sh)**  
4. Run the **[Consensus Controller](/Simulation%20Gazebo/Controller.py)**  
5. Execute the **[Leader Trajectory](/Simulation%20Gazebo/circle.py)**  

### Video Preview 
[![Download the Video](/Media/Simulation.jpeg)](/Media/Simulation.mp4)

## License

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

This project is licensed under the MIT License — see the [LICENSE](./LICENSE) file for details.
