shader_type canvas_item;

uniform vec3 color : source_color = vec3(1.f);
uniform float amount: hint_range(0.f, 1.f) = 0.f;

void fragment() {
	vec3 original_color = texture(TEXTURE, UV).rgb;
	COLOR.rgb = mix(original_color, color, amount);
}