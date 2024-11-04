# Tutorial (~ 1 minute)

## Setup(10 seconds) 
1. clone repo
```
git clone https://github.com/WrongAnswer2/icpc-training.git

```
2. install pip
```
pip install mkdocs
pip install mkdocs-material
pip install pyyaml

```
3. local serve website
```
cd icpc-training
mkdocs serve
```
## Adding records (10 seconds)
1. add entry in records.xlsx
2. run the following
```
python auto_record.py
```
## updating records (10 seconds)

update the corresponding markdown files

![image](https://github.com/user-attachments/assets/12a5f237-213b-44d6-a326-2980eacb8b4a)

## removing records (10 seconds)

run the following
```
python remove.record.py
```

## push + host github page
copy the following and paste to the terminal directly
```
git add .
git commit -m "Update Document"
git push
mkdocs build
mkdocs gh-deploy

```
