import pandas as pd
import matplotlib.pyplot as plt

CSV_DATA_FILE   = '../csv/stm32_rgb_log.csv';
CSV_SUMMARY_FILE  = '../csv/plot_summary.csv';
PNG_LOCATION = '../stm32_dashboard.png';

def plot_analysis():
    df = pd.read_csv(CSV_DATA_FILE);
    df_summary = pd.read_csv(CSV_SUMMARY_FILE);

    fig, axes = plt.subplots(2, 3, figsize = (12, 8));

    axes[0, 0].plot(df['time_ms'], df['red_pct'], color = 'tab:red', label = 'red percent');
    axes[0, 0].set(title = 'red percent value', ylabel = 'red_pct');
    axes[0, 0].legend();
    axes[0, 0].grid(alpha = 0.3);

    axes[1, 0].plot(df['time_ms'], df['red_raw'], color = 'tab:red', label = 'red raw value');
    axes[1, 0].set(title = 'red raw value', xlabel = 'time_ms', ylabel = 'red_raw');
    axes[1, 0].legend();
    axes[1, 0].grid(alpha = 0.3);

    axes[0, 1].plot(df['time_ms'], df['green_pct'], color = 'tab:green', label = 'green percent');
    axes[0, 1].set(title = 'green percent value', ylabel = 'green_pct');
    axes[0, 1].legend();
    axes[0, 1].grid(alpha = 0.3);

    axes[1, 1].plot(df['time_ms'], df['green_raw'], color = 'tab:green', label = 'green raw');
    axes[1, 1].set(title = 'green raw value', xlabel = 'time_ms', ylabel = 'green raw value');
    axes[1, 1].legend();
    axes[1, 1].grid(alpha = 0.3);

    axes[0, 2].plot(df['time_ms'], df['blue_pct'], color = 'tab:blue', label = 'blue percent');
    axes[0, 2].set(title = 'blue percent value', ylabel = 'blue_pct');
    axes[0, 2].legend();
    axes[0, 2].grid(alpha = 0.3);

    axes[1, 2].plot(df['time_ms'], df['blue_raw'], color = 'tab:blue', label = 'blue raw');
    axes[1, 2].set(title = 'blue raw value', xlabel = 'time_ms', ylabel = 'blue raw value');
    axes[1, 2].legend();
    axes[1, 2].grid(alpha = 0.3);

    summary = (f'RED: Max: {df['red_pct'].mean():.2f}, Min: {df['red_pct'].min()}, Max: {df['red_pct'].max()}\n'
               f'GREEN: Max: {df['green_pct'].mean():.2f}, Min: {df['green_pct'].min()}, Max: {df['green_pct'].max()}\n'
               f'BLUE: Max: {df['blue_pct'].mean():.2f}, Min: {df['blue_pct'].min()}, Max: {df['blue_pct'].max()}\n');

    fig.suptitle('STM32 RGB Dashboard', fontsize = 16);
    fig.text(0.02, 0.02, summary, fontsize = 10);
    fig.tight_layout(rect = [0, 0.1, 1, 1]);
    fig.savefig(PNG_LOCATION, dpi = 400);
    plt.show();

def analyse_data():
    df = pd.read_csv(CSV_DATA_FILE);
    data = {'metric': ['time_ms', 'red_pct', 'red_raw', 'green_pct', 'green_raw', 'blue_pct', 'blue_raw'],
            'mean': [df['time_ms'].mean(), df['red_pct'].mean(), df['red_raw'].mean(), df['green_pct'].mean(), df['green_raw'].mean(), df['blue_pct'].mean(), df['blue_raw'].mean(),],
            'min': [df['time_ms'].min(), df['red_pct'].min(), df['red_raw'].min(), df['green_pct'].min(), df['green_raw'].min(), df['blue_pct'].min(), df['blue_raw'].min(),],
            'max': [df['time_ms'].max(), df['red_pct'].max(), df['red_raw'].max(), df['green_pct'].max(), df['green_raw'].max(), df['blue_pct'].max(), df['blue_raw'].max(),]};
    summary = pd.DataFrame(data);
    summary.to_csv(CSV_SUMMARY_FILE, index = False);
    print(summary);

def main():
    analyse_data();
    plot_analysis();

if __name__ == '__main__':
    main();