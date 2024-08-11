extends Bullet

func _on_hit_sound_finished():
	queueFree()

func _on_time_to_live_timeout():
	queueFree()
