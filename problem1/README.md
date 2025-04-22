## **git lfs**

```
git lfs install
git lfs pull
```

## **Generate optimized codes**

Export your openai api-key
```
export OPENAI_API_KEY=<your-api-key>
```

Generate codes to `./logs/<model>`
```
bash run.sh
```

## **Evaluate optimized codes**
```
bash eval.sh
```

## **Test ParEval**
Compiling the required driver.
```
cd ParEval/drivers/cpp/ && make && cd ../../..
```
Testing using pytest.
```
pytest -v
```