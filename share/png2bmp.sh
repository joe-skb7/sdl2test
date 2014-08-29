#!/bin/bash

in_file="rock-tux.png"
out_file=${in_file/%.*}.bmp

check_imagemagick() {
	convert &>/dev/null
	if [ $? -ne 0 ]; then
		echo " ** Error: \"convert\" tool not found" >&2
		echo "    Please install \"imagemagick\" first" >&2
		echo "    To do so run next command:" >&2
		echo "    $ sudo aptitude install imagemagick" >&2
		exit 1
	fi
}

check_in_file() {
	if [ ! -f $in_file ]; then
		echo " ** Error: \"$in_file\" file not found" >&2
		exit 1
	fi
}

convert_image() {
	# Convert from PNG to BMP with removing alpha-channel
	convert -flatten $in_file $out_file
}

check_imagemagick
check_in_file
convert_image
