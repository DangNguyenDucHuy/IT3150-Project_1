from config.run import setup_config
from collector.run import run_collector



def run_pipeline():
    setup_config()
    run_collector()



if __name__ == "__main__":
    run_pipeline()
