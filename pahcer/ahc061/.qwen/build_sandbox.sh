SCRIPT_DIR=$(cd $(dirname "${BASH_SOURCE[0]}") && pwd)
docker build --network host -f "${SCRIPT_DIR}/sandbox.dockerfile" -t kyopro_ahc061_qwen_sandbox "${SCRIPT_DIR}/.."