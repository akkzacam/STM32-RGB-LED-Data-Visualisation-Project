# STM32 RGB LED Data Visualisation Project

## Project Overview

This project uses three potentiometers to control the red, green, and blue channels of an RGB LED. An STM32F446RE microcontroller reads the potentiometer values using ADC, converts the readings into PWM duty cycles, and sends the live RGB data to a computer over USART.

Python is then used to read the serial data stream, save the readings into a CSV file, and visualise the RGB percentage values using Matplotlib.

The reference manual is used to check for the addresses and contents for the registers in each peripheral for the STM32F446RE microcontroller.

The goal of this project is to combine:

- Bare-metal STM32 programming using C++
- ADC input reading
- PWM output control
- USART serial communication
- Data visualisation using Python
- Live data visualisation

## System Flow

```text
1. STM32 ADC readings

2. PWM duty cycle update for RGB LED

3. USART2 CSV data stream

4. Python serial reader

5. CSV log + Matplotlib dashboard
```

## Hardware Plan

### ADC Inputs

The STM32 reads three analogue inputs from three potentiometers. Each potentiometer controls one RGB LED colour channel.

```text
ADC1 Channel 0 -> PA0 -> Red potentiometer
ADC1 Channel 1 -> PA1 -> Blue potentiometer
ADC1 Channel 4 -> PA4 -> Green potentiometer
```

Each raw ADC value is converted into a percentage ranging from `0%` to `100%`.

### PWM Outputs

TIM2 generates PWM signals for the RGB LED.

```text
TIM2 Channel 1 -> PA5  -> Red LED segment
TIM2 Channel 2 -> PB3  -> Blue LED segment
TIM2 Channel 3 -> PB10 -> Green LED segment
```

The PWM duty cycle for each channel is controlled by its corresponding potentiometer reading.

### USART Output

USART2 sends the RGB data to the computer using a CSV-style text format.

```text
USART2_TX -> PA2
USART2_RX -> PA3
```

Expected serial format:

```csv
time_ms,red_raw,red_pct,blue_raw,blue_pct,green_raw,green_pct
0,2048,50,1000,24,3500,85
100,2050,50,1100,26,3400,83
```

### Sampling Timer

TIM3 controls the sampling rate using an interrupt using a sampling of 100ms. This gives a readable update rate for both the RGB LED and the Python dashboard.

## Firmware Responsibilities

The STM32 firmware will:

1. Configure ADC1 for three input channels.
2. Configure TIM2 for three PWM output channels.
3. Configure USART2 for serial transmission.
4. Configure TIM3 to trigger periodic sampling.
5. Read the three ADC channels for every sampling period.
6. Convert ADC values into percentage values.
7. Update the PWM duty cycle for each RGB LED channel.
8. Transmit one CSV row over USART2 per sample.

## Python Data Visualisation Plan

Python reads the USART2 data stream while the STM32 is running.

```text
1. STM32 CSV row

2. Python serial read

3. append to CSV

4. update Matplotlib plot
```

The Python program will:

1. Read serial data from the STM32.
2. Parse and save each CSV row into `<filename_for_log>.csv`.
3. Plot `red_pct`, `blue_pct`, and `green_pct` against `time_ms`.
4. Keep only the latest 200 points visible during live plotting.
5. Generate a summary CSV after the run.
6. Save a final dashboard image.

## Planned Python Project Structure

```text
python_dashboard/
|-- src/
|   |-- live_dashboard.py
|   |-- plot_analysis.py
|
|-- csv/
|   |-- <filename_log>.csv
|   |-- <filename_summary>.csv
|
|-- output/
|   |-- <literally_name_this_anything>.png
```

## Data Analysis Outputs

After collecting data, the Python scripts will produce:

- a complete CSV log of all RGB readings
- a summary CSV containing mean, minimum, and maximum values for each RGB channel
- a Matplotlib line plot showing RGB percentage over time
- a saved dashboard image for documentation

## Notes

This project is mainly for practicing an end-to-end embedded data workflow:

```text
1. Hardware signal

2. Firmware processing

3. Serial communication

4. Python logging

5. Data visualisation
```

It connects low-level embedded programming with higher-level Python analysis, which is the main engineering skill being developed in this project. I'm too lazy to include the schematics. ATP, you should probably have sufficient circuit theory to wire up the prototype.
