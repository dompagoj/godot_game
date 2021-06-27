extends Label

var TIMER_LIMIT = 0.5
var timer = 0.5

func _process(delta):
	timer += delta
	if (timer >= TIMER_LIMIT):
		text = String(Engine.get_frames_per_second())
		timer = 0
