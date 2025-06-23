programName = "BlockBreakPy"
programVersion = "1.2"
renderWidth = 640
renderHeight = 472
fontHeight = 16
playerSpeed = renderHeight / 59
playerWidth = renderWidth / 40
playerHeight = renderWidth / 40
playerStartX = (renderWidth / 2) - (playerWidth / 2)
playerStartY = renderHeight - (playerHeight * 3)
if (playerSpeed < 1):
    playerSpeed = 1
if (playerWidth < 1):
    playerWidth = 1
if (playerHeight < 1):
    playerHeight = 1
screenEdgeUp = 0
screenEdgeDown = renderHeight - playerHeight
screenEdgeLeft = 0
screenEdgeRight = renderWidth - playerWidth
maxBlocks = 255
maxFPS = 30
