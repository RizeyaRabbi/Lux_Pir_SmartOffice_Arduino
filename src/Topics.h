#ifndef TOPICS_H
#define TOPICS_H

const char *subscriptionToics[] = {
    "SO/2F/O/R0/L0",
    "SO/2F/O/R0/L1",
    "SO/2F/O/R1/L0",
    "SO/2F/O/R1/L1",
    "SO/2F/O/R2/L0",
    "SO/2F/O/R2/L1",
    "SO/2F/O/R3/L0",
    "SO/2F/O/R3/L1",
    "SO/2F/O/R4/L0",
    "SO/2F/O/R4/L1",
    "SO/2F/O/R5/L0",
    "SO/2F/O/R5/L1",
    "SO/2F/O/MR/L",
    "SO/2F/O/WO/D",
    "SO/2F/O/W1/L0",
    "SO/2F/O/W1/L1",
    "SO/2F/O/AL/ON",
    "SO/2F/O/AL/OFF",
    "SO/2F/O/AL/Auto",
    "SO/2F/O/AL/Pat",
    "SO/2F/I/LS/R0/S0",
    "SO/2F/O/AL/DT"};

/*MQTT Device Status Topic*/
const char *deviceStatus_topic = "SO/2F/DS/C";

/*MQTT PIR Sensor Topic*/
const char *row0_sensor0_topic = "SO/2nd_Floor/Input/PIRSensor/Row0/Sensor0";
const char *row0_sensor1_topic = "SO/2nd_Floor/Input/PIRSensor/Row0/Sensor1";
const char *row0_sensor2_topic = "SO/2nd_Floor/Input/PIRSensor/Row0/Sensor2";
const char *row0_sensor3_topic = "SO/2nd_Floor/Input/PIRSensor/Row0/Sensor3";
const char *row0_sensor4_topic = "SO/2nd_Floor/Input/PIRSensor/Row0/Sensor4";
const char *row0_sensor5_topic = "SO/2nd_Floor/Input/PIRSensor/Row0/Sensor5";
const char *row0_sensor6_topic = "SO/2nd_Floor/Input/PIRSensor/Row0/Sensor6";
const char *row0_sensor7_topic = "SO/2nd_Floor/Input/PIRSensor/Row0/Sensor7";
const char *row0_sensor8_topic = "SO/2nd_Floor/Input/PIRSensor/Row0/Sensor8";
const char *row0_sensor9_topic = "SO/2nd_Floor/Input/PIRSensor/Row0/Sensor9";

const char *row1_sensor0_topic = "SO/2nd_Floor/Input/PIRSensor/Row1/Sensor0";
const char *row1_sensor1_topic = "SO/2nd_Floor/Input/PIRSensor/Row1/Sensor1";
const char *row1_sensor2_topic = "SO/2nd_Floor/Input/PIRSensor/Row1/Sensor2";
const char *row1_sensor3_topic = "SO/2nd_Floor/Input/PIRSensor/Row1/Sensor3";
const char *row1_sensor4_topic = "SO/2nd_Floor/Input/PIRSensor/Row1/Sensor4";
const char *row1_sensor5_topic = "SO/2nd_Floor/Input/PIRSensor/Row1/Sensor5";
const char *row1_sensor6_topic = "SO/2nd_Floor/Input/PIRSensor/Row1/Sensor6";

const char *row2_sensor0_topic = "SO/2nd_Floor/Input/PIRSensor/Row2/Sensor0";
const char *row2_sensor1_topic = "SO/2nd_Floor/Input/PIRSensor/Row2/Sensor1";
const char *row2_sensor2_topic = "SO/2nd_Floor/Input/PIRSensor/Row2/Sensor2";
const char *row2_sensor3_topic = "SO/2nd_Floor/Input/PIRSensor/Row2/Sensor3";
const char *row2_sensor4_topic = "SO/2nd_Floor/Input/PIRSensor/Row2/Sensor4";

const char *row3_sensor0_topic = "SO/2nd_Floor/Input/PIRSensor/Row3/Sensor0";
const char *row3_sensor1_topic = "SO/2nd_Floor/Input/PIRSensor/Row3/Sensor1";
const char *row3_sensor2_topic = "SO/2nd_Floor/Input/PIRSensor/Row3/Sensor2";
const char *row3_sensor3_topic = "SO/2nd_Floor/Input/PIRSensor/Row3/Sensor3";

const char *row4_sensor0_topic = "SO/2nd_Floor/Input/PIRSensor/Row4/Sensor0";
const char *row4_sensor1_topic = "SO/2nd_Floor/Input/PIRSensor/Row4/Sensor1";
const char *row4_sensor2_topic = "SO/2nd_Floor/Input/PIRSensor/Row4/Sensor2";
const char *row4_sensor3_topic = "SO/2nd_Floor/Input/PIRSensor/Row4/Sensor3";
const char *row4_sensor4_topic = "SO/2nd_Floor/Input/PIRSensor/Row4/Sensor4";
const char *row4_sensor5_topic = "SO/2nd_Floor/Input/PIRSensor/Row4/Sensor5";

const char *row5_sensor0_topic = "SO/2nd_Floor/Input/PIRSensor/Row5/Sensor0";
const char *row5_sensor1_topic = "SO/2nd_Floor/Input/PIRSensor/Row5/Sensor1";
const char *row5_sensor2_topic = "SO/2nd_Floor/Input/PIRSensor/Row5/Sensor2";
const char *row5_sensor3_topic = "SO/2nd_Floor/Input/PIRSensor/Row5/Sensor3";
const char *row5_sensor4_topic = "SO/2nd_Floor/Input/PIRSensor/Row5/Sensor4";
const char *row5_sensor5_topic = "SO/2nd_Floor/Input/PIRSensor/Row5/Sensor5";
const char *row5_sensor6_topic = "SO/2nd_Floor/Input/PIRSensor/Row5/Sensor6";

const char *washRoom1_sensor0_topic = "SO/2nd_Floor/Input/PIRSensor/WashRoom1/Sensor0";
const char *washRoom1_sensor1_topic = "SO/2nd_Floor/Input/PIRSensor/WashRoom1/Sensor1";
const char *washRoom1_sensor2_topic = "SO/2nd_Floor/Input/PIRSensor/WashRoom1/Sensor2";
const char *washRoom1_sensor3_topic = "SO/2nd_Floor/Input/PIRSensor/WashRoom1/Sensor3";

const char *washRoom0_sensor0_topic = "SO/2nd_Floor/Input/PIRSensor/WashRoom0/Sensor0";

const char *mainRoom_sensor_topic = "SO/2nd_Floor/Input/PIRSensor/MainRoom/Sensor0";

#endif