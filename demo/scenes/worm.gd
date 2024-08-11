extends Worm

func _on_area_entered(area):
	if area is Bullet:
		onAreaEntered(area)

func _on_body_entered(body):
	if body is Player:
		onPlayerCollision(body)

func _on_body_exited(body):
	if body is Player:
		onPlayerEscaped()

func _on_border_area_body_entered(_body):
	changeDirectionAndFlip()
func _on_cliff_area_body_exited(_body):
	changeDirectionAndFlip()
func _on_cliff_area_1_body_exited(_body):
	changeDirectionAndFlip()
