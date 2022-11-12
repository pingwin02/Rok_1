#!/bin/bash
date > /home/pingwin/public_html/info.txt
ps -ef | head -59 >> /home/pingwin/public_html/info.txt
