FROM python:3.10-slim-buster

WORKDIR /gdelt

COPY requirements.txt requirements.txt

RUN pip3 install -r requirements.txt

COPY gdeltconfig.py .
COPY gdeltgrabber.py .

CMD ["python3", "gdeltgrabber.py"]