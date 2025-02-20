#base
echo "base"
python generate.py --models gpt-4o-mini

#s-p norag
echo "s-p norag"
python generate.py --models gpt-4o-mini --two-stage true --serial-rag false --parallel-rag false --check false 

#s rag then p
echo "s rag then p"
python generate.py --models gpt-4o-mini --two-stage true --serial-rag true --parallel-rag false --check false 
#s rag p rag
echo "s rag p rag"
python generate.py --models gpt-4o-mini --two-stage true --serial-rag true --parallel-rag true --check false
#check
echo "add check"
python generate.py --models gpt-4o-mini --two-stage true --serial-rag true --parallel-rag true --check true 