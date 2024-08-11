extends Gun

func _on_body_entered(body):
	if body is Player:
		onBodyEntered(body)
