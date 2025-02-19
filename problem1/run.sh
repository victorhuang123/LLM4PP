#base
echo "base"
python evaluation.py --models gpt-4o-mini > base_out

#s-p norag
echo "s-p norag"
python evaluation.py --models gpt-4o-mini --two-stage true --serial-rag false --parallel-rag false --check false > norag_out

#s rag then p
echo "s rag then p"
python evaluation.py --models gpt-4o-mini --two-stage true --serial-rag true --parallel-rag false --check false > s_rag_p_norag

#s rag p rag
echo "s rag p rag"
python evaluation.py --models gpt-4o-mini --two-stage true --serial-rag true --parallel-rag true --check false > s_rag_p_rag

#check
echo "add check"
python evaluation.py --models gpt-4o-mini --two-stage true --serial-rag true --parallel-rag true --check true > check
