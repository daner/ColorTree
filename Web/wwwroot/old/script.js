$(function() {
	$('#sendButton').click(function() {
		var picker = $('#colorinput')[0].jscolor;

		var colorObject = {
			r: Math.round(picker.rgb[0]),
			g: Math.round(picker.rgb[1]),
			b: Math.round(picker.rgb[2])
		};

		//console.log(colorObject);

		$.ajax({
			type: "POST",
			url: "/color",
			data: JSON.stringify(colorObject),
			contentType: "application/json; charset=utf-8",
			dataType: "json",
			success: function (data) { console.log(data); }
		});

	});

	$('#sendFileButton').click(function () {
	    var formData = new FormData($('form')[0]);
	    $.ajax({
	        url: '/load',
	        type: 'POST',
	        xhr: function () {  
	            var myXhr = $.ajaxSettings.xhr();
	             return myXhr;
	        },

	        data: formData,
	        cache: false,
	        contentType: false,
	        processData: false
	    });
	});
});