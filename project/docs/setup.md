# Setup

## 1. Description

+ Working directory is `project/`
+ OS: Windows
+ IDE: VSCode, Google Colab
+ About how the system works, check [`pipeline.md`](./pipeline.md)


## 2. Get started

### Step 1 - Python venv

```bash
python -m venv .venv
.venv/Scripts/Activate
```

### Step 2 - Install libs

Change to current working directory
```bash
cd project
```

Define dependencies in `pyproject.toml` and run command to install
```bash
pip install -e .
```

>[!NOTE]
> Because the pipeline use `yt-dlp` library to download videos, which needs **FFmpeg** tool to handle, so install that tool on its official website, then write down the absolute path to its `bin/` folder in the `.env` file created later.

### Step 3 - Define env variables

```bash
cp .env.example .env
```

And set value for `.env`'s variables

### Step 4 - Run the main pipeline

```bash
python -m src.main
```
