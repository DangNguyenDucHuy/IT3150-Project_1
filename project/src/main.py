from config.run import setup_config
from collector.run import run_collector
from preprocessor.run import run_preprocessor



def run_pipeline():
    setup_config()
    run_collector()
    run_preprocessor()



if __name__ == "__main__":
    run_pipeline()
