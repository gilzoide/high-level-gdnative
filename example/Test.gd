extends Node

const gdnlib = preload("res://example_gdnativelibrary.tres")


func _ready() -> void:
	var gdnative = GDNative.new()
	gdnative.library = gdnlib
	gdnative.initialize()
