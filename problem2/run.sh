#unset HTTP_PROXY HTTPS_PROXY http_proxy https_proxy
export no_proxy=127.0.0.1,localhost
export NO_PROXY=127.0.0.1,localhost
export PYTHONUNBUFFERED=1

#base
echo "base"
python generate.py --models local_model

#s-p norag
echo "s-p norag"
python generate.py --models local_model --two-stage true --serial-rag false --parallel-rag false --check false 

#s rag then p
echo "s rag then p"
python generate.py --models local_model --two-stage true --serial-rag true --parallel-rag false --check false 

#s rag p rag
echo "s rag p rag"
python generate.py --models local_model --two-stage true --serial-rag true --parallel-rag true --check false

