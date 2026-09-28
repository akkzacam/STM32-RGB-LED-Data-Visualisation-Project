import serial
import csv
import matplotlib.pyplot as plt
from collections import deque

PORT = '/dev/cu.usbmodem1103';
BAUD_RATE = 115200;
CSV_FILE = '../csv/stm32_rgb_log.csv';
MAX_POINTS = 200;

def print_serial():
    with serial.Serial(PORT, BAUD_RATE, timeout = 1) as ser, open(CSV_FILE, 'w', newline = '') as file:
        csv.writer(file).writerow(['time_ms', 'red_pct', 'red_raw', 'green_pct', 'green_raw', 'blue_pct', 'blue_raw']);

        while True:
            line = ser.readline().decode('utf-8', errors = 'replace').strip();
            if not line or line.startswith('red_pct'):
                continue;

            try:
                row = [int(value) for value in line.split(',')];

            except ValueError:
                continue;

            if len(row) != 7:
                continue;

            csv.writer(file).writerow(row);
            file.flush();
            print(row);


def live_dashboard():
    time_ms_val     = deque(maxlen = MAX_POINTS);
    red_pct_val     = deque(maxlen = MAX_POINTS);
    red_raw_val     = deque(maxlen = MAX_POINTS);
    green_pct_val   = deque(maxlen = MAX_POINTS);
    green_raw_val   = deque(maxlen = MAX_POINTS);
    blue_pct_val    = deque(maxlen = MAX_POINTS);
    blue_raw_val    = deque(maxlen = MAX_POINTS);

    plt.ion();

    fig, axes = plt.subplots(2, 3, figsize = (10, 7), sharex = True);
    red_pct_val_line, = axes[0, 0].plot([], [], color = 'tab:red', label = 'red percent');
    axes[0, 0].set(title = 'red percent value', ylabel = 'red_pct');
    axes[0, 0].legend();
    axes[0, 0].grid(alpha = 0.3);

    red_raw_val_line, = axes[1, 0].plot([], [], color = 'tab:red', label = 'red raw value');
    axes[1, 0].set(title = 'red raw value', xlabel = 'time_ms', ylabel = 'red_raw');
    axes[1, 0].legend();
    axes[1, 0].grid(alpha = 0.3);

    green_pct_val_line, = axes[0, 1].plot([], [], color = 'tab:green', label = 'green percent');
    axes[0, 1].set(title = 'green percent value', ylabel = 'green_pct');
    axes[0, 1].legend();
    axes[0, 1].grid(alpha = 0.3);

    green_raw_val_line, = axes[1, 1].plot([], [], color = 'tab:green', label = 'green raw');
    axes[1, 1].set(title = 'green raw value', xlabel = 'time_ms', ylabel = 'green raw value');
    axes[1, 1].legend();
    axes[1, 1].grid(alpha = 0.3);

    blue_pct_val_line, = axes[0, 2].plot([], [], color = 'tab:blue', label = 'blue percent');
    axes[0, 2].set(title = 'blue percent value', ylabel = 'blue_pct');
    axes[0, 2].legend();
    axes[0, 2].grid(alpha = 0.3);

    blue_raw_val_line, = axes[1, 2].plot([], [], color = 'tab:blue', label = 'blue raw');
    axes[1, 2].set(title = 'blue raw value', xlabel = 'time_ms', ylabel = 'blue raw value');
    axes[1, 2].legend();
    axes[1, 2].grid(alpha = 0.3);

    with serial.Serial(PORT, BAUD_RATE, timeout = 1) as ser, open(CSV_FILE, 'w', newline = '') as file:
        csv.writer(file).writerow(['time_ms', 'red_pct', 'red_raw', 'green_pct', 'green_raw', 'blue_pct', 'blue_raw']);

        while True:
            line = ser.readline().decode('utf-8', errors = 'replace').strip();

            if not line or line.startswith('red_pct'):
                continue;

            parts = line.split(',');

            if len(parts) != 7:
                continue;

            try:
                time_ms     = int(parts[0]);
                red_pct     = int(parts[1]);
                red_raw     = int(parts[2]);
                green_pct   = int(parts[3]);
                green_raw   = int(parts[4]);
                blue_pct    = int(parts[5]);
                blue_raw    = int(parts[6]);
            
            except ValueError:
                continue;

            csv.writer(file).writerow([time_ms, red_pct, red_raw, green_pct, green_raw, blue_pct, blue_raw]);
            file.flush();

            time_ms_val.append(time_ms);
            red_pct_val.append(red_pct);
            red_raw_val.append(red_raw);
            green_pct_val.append(green_pct);
            green_raw_val.append(green_raw);
            blue_pct_val.append(blue_pct);
            blue_raw_val.append(blue_raw);

            red_pct_val_line.set_data(time_ms_val, red_pct_val);
            red_raw_val_line.set_data(time_ms_val, red_raw_val);
            green_pct_val_line.set_data(time_ms_val, green_pct_val);
            green_raw_val_line.set_data(time_ms_val, green_raw_val);
            blue_pct_val_line.set_data(time_ms_val, blue_pct_val);
            blue_raw_val_line.set_data(time_ms_val, blue_raw_val);

            axes[0, 0].relim();
            axes[0, 0].autoscale_view();
            axes[1, 0].relim();
            axes[1, 0].autoscale_view();
            axes[0, 1].relim();
            axes[0, 1].autoscale_view();
            axes[1, 1].relim();
            axes[1, 1].autoscale_view();
            axes[0, 2].relim();
            axes[0, 2].autoscale_view();
            axes[1, 2].relim();
            axes[1, 2].autoscale_view();

            plt.pause(0.01);

def main():
    #print_serial();
    live_dashboard();

if __name__ == '__main__':
    main();