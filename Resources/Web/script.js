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
});