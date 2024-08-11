extends Bee

func _on_area_entered(area):
	if area is Bullet:
		onAreaEntered(area)

func _on_body_entered(body):
	if body is Player:
		onPlayerCollision(body)

func _on_body_exited(body):
	if body is Player:
		onPlayerEscaped()

func _on_aggro_body_entered(_body):
	onAggroBodyEntered()
func _on_aggro_body_exited(_body):
	onAggroBodyExited()
