// JavaScript generator of random true-color bitmaps
// Copyright (c) 2015, 2018 Lev Vorobjev

var canvas = document.getElementsByTagName("canvas").item(0);
var image = document.getElementsByTagName("img").item(0);

document.body.onload = function()
{
	var height = window.document.documentElement.clientHeight -4;
	var width = window.document.documentElement.clientWidth -4;
	image.width = canvas.width = width;
	image.height = canvas.height = height;
	renewImage();
	window.setInterval(renewImage,5000);
}

function renewImage()
{
	var context = canvas.getContext('2d');
	var imageData = context.getImageData(0, 0, canvas.width, canvas.height);
	context.putImageData(fillcolor(imageData), 0, 0);
	image.src = canvas.toDataURL();
}

function fillcolor(imageData)
{
	var pixels = imageData.data;
	pixels[0] = Math.floor(Math.random()*256);
	pixels[1] = Math.floor(Math.random()*256);
	pixels[2] = Math.floor(Math.random()*256);
	pixels[3] = 255;
	for (var i = 4; i < canvas.width*4; i++)
	{
		if(i%4 != 3) pixels[i] = pixels[i-4] + 5*Math.round(Math.random() - Math.random());
		else pixels[i] = pixels[i-4]; 
	}
	for (var i = canvas.width*4; i < pixels.length; i++)
	{
		if(i%4 != 3)
		{
			if(i%(canvas.width*4) != 0) pixels[i] = (pixels[i-4]+pixels[i-canvas.width*4])/2 + 5*Math.round(Math.random() - Math.random());
			else pixels[i] = pixels[i-canvas.width*4] + 5*Math.round(Math.random() - Math.random());
		}
		else pixels[i] = pixels[i-4]; 	
	}
	return imageData;
}
