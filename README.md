# OBR 2019

The Olympiad's main idea is to build a robot and simulate a rescue operation. In other words, our robot needed capable to overcome irregular terrain, cross unknown paths, divert from obstacles and rise inclinations for rescuing the victims and transport them to a safe spot. This year, my team and I decided to use an Arduino Mega + Raspberry Pi 3B.

<p align="center">
<img src="https://user-images.githubusercontent.com/62116654/123113460-f5034a00-d414-11eb-8d78-50f539556f81.jpeg">
</p>


# Arduino

The Arduino was used for the most of things that we needed to do, such things as follow the line, detect and dodge obstacles.

# Raspberry Pi

The Raspberry was used for image proccessing. It was really helpfull for detecting color, checking points, victims, ramps, and also helping the line-follower.

Pre-req.: OpenCV

<p align="center">
<img src="https://user-images.githubusercontent.com/62116654/123113781-34319b00-d415-11eb-89eb-d71d1a9af7ec.jpeg">
</p>


# Arduino + Raspberry Communication

We opted to use i2c
