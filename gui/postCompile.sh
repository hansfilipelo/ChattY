#!/bin/bash

if [ -d ChattY.app ]
then
	cp build/apple_sms.wav ChattY.app/Contents/Resources/
	cp build/bombo.wav ChattY.app/Contents/Resources/
fi

