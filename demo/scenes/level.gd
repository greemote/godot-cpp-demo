extends Level

func _on_player_shoot(pos, facingRight):
	onPlayerShoot(pos, facingRight)

func _on_enemies_child_exiting_tree(_node):
	onEnemiesChildExitingTree()
