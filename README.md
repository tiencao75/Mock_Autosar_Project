# Mock_Autosar_Project
# Engine Cooling System

## Overview
The Engine Cooling System is designed to monitor and manage the engine temperature effectively. This system utilizes ultrasonic sensors and actuators to regulate the cooling process, ensuring optimal engine performance and safety. Key functions include continuous temperature monitoring, activation of cooling fans, water pump control, overheat protection, and diagnostic error logging.

![Hình ảnh hệ thống làm mát động cơ](https://github.com/tiencao75/Mock_Autosar_Project/blob/main/z6413832225423_1319b9df19a9162e51ab2a3acafe38e4.jpg?raw=true)
<!-- Nếu cần điều chỉnh kích thước, bạn có thể dùng HTML -->
<!-- <img src="URL_hình_ảnh_1" width="500"> -->

## Features
![Features](https://github.com/tiencao75/Mock_Autosar_Project/blob/main/z6413832689867_af4647b1c5a4e8741c1e06836e3b9a04.jpg?raw=true)
- **Temperature Monitoring**: Continuously reads engine and ambient air temperature from sensors.
- **Cooling Fan Activation**: Sends signals to activate the cooling fan when necessary.
- **Water Pump Control**: Adjusts the water pump speed based on cooling demands.
- **Overheat Protection**: Triggers emergency cooling measures when overheating is detected.
- **Diagnostic Reporting**: Detects faults in sensors and actuators, logging error codes for troubleshooting.

## Software Components (SWC)
- **EngineTemperatureSensor**: Reads engine temperature and provides data for processing.
- **EngineTemperatureControl**: Manages the cooling system based on sensor inputs, adjusts fan and pump speeds, and handles diagnostic reporting.
- **EngineTemperatureActuator**: Controls the speed of the water pump, cooling fan, and activates the warning light if the engine temperature exceeds thresholds.
- **NVBlock**: Stores and retrieves system configuration and parameters in non-volatile memory.
- **Parameter**: Provides calibration data for temperature control and system configuration.

## ECU Allocation
![Sơ đồ SWC mapping](https://github.com/tiencao75/Mock_Autosar_Project/blob/main/z6413834761491_68636943e8a1603ebf1fc375b0973de1.jpg?raw=true)
<!-- Nếu cần điều chỉnh kích thước, bạn có thể dùng HTML -->
<!-- <img src="URL_hình_ảnh_2" width="500"> -->

- **ECU_01**:
  - Hosts **EngineTemperatureSensor** (Runnables: `GetEngineTemperature`, `GetAirTemperature`).
  - Hosts **EngineTemperatureControl** (Runnables: `CalcCoolingSpeed`, `SendControlSignal`).
  - Hosts **NVBlock** (Runnables: `WriteErrorToNVM`, `ReadErrorToNVM`).
  - Hosts **Parameter** (Runnable: `ProvideCalibrationData`).
- **ECU_02**:
  - Hosts **EngineTemperatureActuator** (Runnables: `ChangeSpeedEnginePump`, `ChangeSpeedEngineFan`, `ChangeEngineTemperatureWarningLight`, `ReadControlSignal`).
