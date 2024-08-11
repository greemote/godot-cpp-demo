extends Player

func _on_cooldown_timer_timeout():
	resetCooldown()

func _on_fire_timer_timeout():
	fireTimeout()

func _on_invisible_frames_timeout():
	setVulnerableTrue()
