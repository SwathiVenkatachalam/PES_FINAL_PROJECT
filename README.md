# PES Final Project
## Musical Notes Player based on-board MMA8451Q Accelerometer over I2C

### Project source code: <br/>
https://github.com/ECEN5813/final-project-SwathiVenkatachalam/tree/main/source <br/>

### Project proposal: <br/>
https://github.com/ECEN5813/final-project-SwathiVenkatachalam/blob/main/Documents/PES_Project_Proposal.pdf <br/>

### Project test plan and final report: <br/>
https://github.com/ECEN5813/final-project-SwathiVenkatachalam/blob/main/Documents/Test%20Plan_Final%20Report.pdf <br/>

### Project Demo Video:  <br/>
https://drive.google.com/file/d/1FRDMXOhVGObR3DemkXkreL1L0wENK2KZ/view?usp=sharing <br/>

### Project Functionality Matches the Proposal:<br/>
• Musical Tones Player plays tones based on horizontal plane (roll angle) using 
on-board MMA8451Q Accelerometer over I2C communication.<br/>
• User can move FRDM-KL25Z in horizontal angle (roll) from 0 to 180 degrees. 
(Reference angle: 0 degrees) and it gets detected.<br/>
• User can access the command processor through UART to display the current 
roll angle and to run all the tests. Terminate command works to come out of the 
command processor and to dive into the musical player application. <br/>
• LED indication based on angle measured. <br/>
• Different musical notes that are one second apart are played indefinitely in 
different angle ranges when user moves the KL25Z horizontally.<br/>
• To stop the musical player, user can lay down the board flat. And then reset to 
restart.<br/>

### Block Diagram
![image](https://user-images.githubusercontent.com/112472328/236640511-f36eb467-fcbc-4534-a41c-428bc82c417d.png)<br/>

### Key Learnings
• The integration of I2C and on-board MMA8451 accelerometer. <br/>
• Playing musical notes based on the accelerometer angle sensed.<br/>
• The integration of all modules together to get proper functionality.<br/>
• Developing a good mixture of automated and manual test cases.<br/>

### Challenges
• Getting the DAC output without tearing at the wrap point when the tone 
changes.<br/>
• The musical tones stopped playing in between at random occasions. After a long 
debug session, I figured that if the printf statements are too long, it messes with 
the timer and application throws unreliable working. So, I shortened all the 
printf statements and reduced the number of statements.<br/>

### Future Scope
- Command Processor Menu for selection of different musical tones.
- Smart LED lighting based on the musical tones.
- Add an amplifier circuit, speaker for louder music.




