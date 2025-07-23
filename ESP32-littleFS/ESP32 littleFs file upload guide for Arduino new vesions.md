
-----

# Uploading Files to ESP32 LittleFS via Command Prompt

This guide explains the step-by-step procedure to upload files into the ESP32 LittleFS system using the command line, as the older `.jar` plugin for Arduino IDE is no longer compatible with newer versions. The necessary tools are already available within the ESP32 core folder, and we will execute them manually.

-----

### Tested and Succeeded on:

  * **Operating System:** Ubuntu 22.04.5 LTS
  * **Arduino IDE Version:** 2.3.6
  * **ESP32 Arduino Core Version (by Espressif):** 3.2.1

-----

## Step 1: Prepare Your Arduino Sketch and Enable Verbose Output

1.  Open **Arduino IDE 2.3.6**.

2.  Go to **File \> Preferences**.

3.  Check the box for "Show verbose output during: **[X] compilation [X] upload**". Click **OK**.

4.  Create a new project using your desired example code.

5.  Enable **debug** and select **full debug** from the Arduino **Tools** drop-down menu.

6.  Enable the **serial monitor** (at the correct baud rate) to see debug messages.

7.  Choose the correct **board** and **COM port** (e.g., ESP32 DevKit V1 and `/dev/ttyUSB0`).

8.  **Compile and upload** your sketch.

Observe the verbose output in the Arduino IDE console during compilation and upload. Look for the serial port (e.g., `/dev/ttyUSB0`) and keep the IDE open for now.

-----

## Step 2: Confirm Partition Scheme for Selected Board

First, you need to confirm which partition scheme your selected board is using.

### Method A: Inspect `boards.txt` (Recommended)

This file explicitly defines the partition scheme for each board. You can use the terminal or a file explorer UI. Here, we'll explain the terminal method.

1.  Open your **terminal**.
2.  Navigate to your ESP32 core installation directory:
    ```bash
    cd ~/.arduino15/packages/esp32/hardware/esp32/3.2.1/
    # IMPORTANT: Adjust '3.2.1' if your ESP32 core version is different.
    ```
3.  Open `boards.txt` with a text editor:
    ```bash
    gedit boards.txt &
    ```
4.  Find your board's definition (e.g., `doitESP32devkitV1`).
5.  Look for the `build.partitions` line. This line specifies the `.csv` file used for the default partition scheme.
    **Example:** `esp32.menu.PartitionScheme.default.build.partitions=default.csv`
    This confirms that `default.csv` is being used for the default partition scheme.

### Method B: Analyze Verbose Upload Output (or full debug on serial monitor)

The verbose output during sketch upload can also reveal the partition table used.

1.  In **Arduino IDE 2.3.6**, upload your sketch again (from Step 1).
2.  Review the verbose output in the black console area.
3.  Search for `partition` or `partition_table.bin`. You might see a line similar to this (though paths and exact filenames can vary):
    ```
    ...write_flash 0x8000 /home/thepasswordisiitdh123/.arduino15/packages/esp32/hardware/esp32/3.2.1/tools/partitions/default_partition_table.bin
    ```
    This indicates that `default_partition_table.bin` (generated from `default.csv`) is being flashed.

-----

## Step 3: Identify LittleFS Partition Details from CSV

Now that you've confirmed the `.csv` file (likely `default.csv`), let's get the exact LittleFS partition details. We'll use the terminal method here.

1.  Open your **terminal**.

2.  Navigate to your ESP32 core's partitions directory:

    ```bash
    cd ~/.arduino15/packages/esp32/hardware/esp32/3.2.1/tools/partitions/
    # IMPORTANT: Adjust '3.2.1' if your ESP32 core version is different.
    ```

3.  Open the identified `.csv` file (e.g., `default.csv`) with a text editor:

    ```bash
    gedit default.csv &
    ```

4.  Locate the **`spiffs` data partition**. Note its **Offset** (flash address) and **Size**.
    From your previous output, this might be (example):

      * **Offset (FLASH\_ADDRESS):** `0x290000`
      * **Size (FILESYSTEM\_SIZE):** `0x160000`

    These values will be used in subsequent commands.

-----

## Step 4: Install/Locate Necessary Command-Line Tools

We need to create a file system image for uploading our files to the ESP32 flash (SPIFFS/LittleFS). `esptool.py` is used as the flasher, and `mklittlefs` is used to create the image file. Both are available in the ESP32 core folder (e.g., `~/.arduino15/packages/esp32/tools`).

For using these tools, you'll need some basic Python tools.

1.  **Install `python3-pip`** (if not already installed):

    ```bash
    sudo apt update
    sudo apt install python3-pip
    ```

2.  **Install `esptool`:**

    ```bash
    pip install esptool
    ```

    Alternatively, you can use the `esptool` present in the ESP32 core folder, similar to how we'll use `mklittlefs`.

3.  **Locate `mklittlefs`:** This tool is usually bundled with the ESP32 Arduino core.

    ```bash
    cd ~/.arduino15/packages/esp32/tools/mklittlefs/3.0.0-gnu12-dc7f933/
    # Replace '3.0.0-gnu12-dc7f933' with your actual version
    ```

    Note the full path to `mklittlefs` (e.g., `~/.arduino15/packages/esp32/tools/mklittlefs/3.0.0-gnu12-dc7f933/mklittlefs`). You'll use this path in the next step.

4.  **(Optional for convenience): Add this path to your system's `PATH` environment variable in `~/.bashrc` to run `mklittlefs` directly.**

    ```bash
    echo 'export PATH="$PATH:/home/thepasswordisiitdh123/.arduino15/packages/esp32/tools/mklittlefs/3.0.0-gnu12-dc7f933/"' >> ~/.bashrc
    source ~/.bashrc
    ```

-----

## Step 5: Prepare Your Data Files

Create a `data` folder inside your sketch directory and place your files there.

1.  Navigate to your sketch directory:
    ```bash
    cd ~/Desktop/My_projects/ESP32-littleFS/
    ```
2.  Create the `data` subfolder and some example files (e.g., `.txt` files).
    ```bash
    mkdir -p data
    echo "This is the first line of text." > data/file1.txt
    echo "Second file content here." > data/file2.txt
    echo "A third file for LittleFS." > data/file3.txt
    ```
3.  Your sketch folder should now look like this:
    ```
    ESP32-littleFS/
    ├── ESP32-littleFS.ino
    └── data/
        ├── file1.txt
        ├── file2.txt
        └── file3.txt
    ```

-----

## Step 6: Generate the LittleFS Image (`.bin` file)

Use `mklittlefs` to create the flashable image from your `data` folder.

1.  Ensure you are in your sketch directory:
    ```bash
    cd ~/Desktop/My_projects/ESP32-littleFS/
    ```
2.  Run the `mklittlefs` command in the terminal:
    ```bash
    # If you added mklittlefs to PATH in step 4:
    mklittlefs -c data -s 0x160000 -p 0x100 littlefs.bin

    # OR, if not in PATH, use the full path:
    # ~/.arduino15/packages/esp32/tools/mklittlefs/3.0.1/mklittlefs -c data -s 0x160000 -p 0x100 littlefs.bin
    ```
    **Note:** `0x160000` is the **FILESYSTEM\_SIZE** from Step 3.

A file named `littlefs.bin` will be created in your current sketch directory.

-----

## Step 7: Flash the LittleFS Image to ESP32

Use `esptool.py` to upload the generated `.bin` file to the ESP32's flash memory.

1.  **Close the Serial Monitor in Arduino IDE.**
2.  Identify your ESP32's serial port (e.g., `/dev/ttyUSB0` from Step 1).
3.  Run the `esptool.py` command:
    ```bash
    esptool.py --chip esp32 --port /dev/ttyUSB0 write_flash 0x290000 littlefs.bin
    ```
    **Note:**
      * Replace `/dev/ttyUSB0` with your actual serial port.
      * `0x290000` is the **FLASH\_ADDRESS (Offset)** from Step 3.
4.  When `esptool.py` shows "Connecting...", **press and hold the "BOOT" button** on your ESP32 board. Release it once the flashing percentage starts to appear.

-----

## Step 8: Verify LittleFS Data on ESP32

Finally, upload your sketch (if not done previously) and check the Serial Monitor to confirm the files are present.

1.  Open the **Serial Monitor** (Tools \> Serial Monitor).
2.  Set the baud rate to **115200** (or your sketch's configured baud rate).
3.  **Restart the board** by pressing the onboard reset button.

You should now see the output from your sketch, listing `file1.txt`, `file2.txt`, and `file3.txt` that you uploaded via the command line\!
