"""
Plots Gyro Z and motor duty cycle over time, and shades the graph according to mission modes
"""

import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import sys

mode_names = {
    0: "Initial Spinup",
    1: "Standby",
    2: "Armed",
    3: "Deployment",
    4: "Despin",
    5: "Controller Spinup",
    6: "Open Loop",
    7: "Automated Sequence",
    8: "Safe Hold"
}

def plot_data(file_name: str) -> None:
    df = pd.read_csv(file_name)

    fig, ax1 = plt.subplots(figsize=(10, 5))
    fig.canvas.manager.set_window_title("Sailing to the Stars Data Viewer")

    ax1.plot(df['Timestamp'], df['Gyro Z'], color='blue', label='Gyro Z', linewidth=1)
    ax1.set_xlabel("Timestamp (ms)")
    ax1.set_ylabel("Gyro Z", color='blue')
    ax1.tick_params(axis='y', labelcolor='blue')

    ax2 = ax1.twinx()
    ax2.plot(df['Timestamp'], df['Duty cycle'], color='red', label='Duty Cycle', linewidth=1)
    ax2.set_ylabel("Duty Cycle", color='red')
    ax2.tick_params(axis='y', labelcolor='red')

    modes = df['Mode'].unique()
    colors = plt.cm.get_cmap('tab10', len(modes))
    for i, mode in enumerate(modes):
        mode_df = df[df['Mode'] == mode]
        mode_name = mode_names.get(mode, f"Mode {mode}")
        ax1.axvspan(mode_df['Timestamp'].min(), mode_df['Timestamp'].max(), 
                    alpha=0.3, color=colors(i), label=mode_name)

    # event_df = df.dropna(subset=['Events'])
    # event_df = event_df[event_df['Events'].astype(str).str.strip() != '']

    # for _, row in event_df.iterrows():
    #     ax1.axvline(x=row['Timestamp'], color='red', linestyle='--', linewidth=1)
    #     ax1.text(row['Timestamp'], max(df['Gyro Z']), str(int(row['Events'])), color='red', fontsize=10, ha='right')

    fig.legend(loc='upper right', bbox_to_anchor=(1, 1))
    plt.title(f"Mission data from {file_name}")
    plt.show()

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python plot_data.py <file>")
        sys.exit(1)
    
    file_name = sys.argv[1]
    plot_data(file_name)