# game211-midstone

View/Hide debug shapes:
| Key | Function |
| --- | --- |
| `F1` | Toggle **image** debug borders |
| `F2` | Toggle **collider** debug borders |

## Using Images
You can import an image and render it using the `ResourceManager` utility class
Example:
```c++
// create an image
int imageID = ResourceManager::getInstance()->AddImage(game, "Art/Desert.png");
// render the image using it's ID, scale and orientation are optinal 
ResourceManager::getInstance()->RenderImage(game, imageID, position, [scale_vec3, orientation_float]);
```

Team members: Devon, Marouane, Tyler
