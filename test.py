import pygame
import math

# Initialize Pygame
pygame.init()

# Set up the window
window_size = (640, 480)
screen = pygame.display.set_mode(window_size)

# Set up the player position, direction and movement speed
player_pos = [320, 240]
player_angle = 0
player_speed = 5

# Main game loop
while True:
    # Handle events
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()

        # Handle key presses
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE:
                pygame.quit()
                sys.exit()

            # Handle movement keys
            elif event.key == pygame.K_w:
                player_pos[0] += math.cos(player_angle) * player_speed
                player_pos[1] += math.sin(player_angle) * player_speed
            elif event.key == pygame.K_s:
                player_pos[0] -= math.cos(player_angle) * player_speed
                player_pos[1] -= math.sin(player_angle) * player_speed
            elif event.key == pygame.K_a:
                player_pos[0] += math.cos(player_angle - math.pi/2) * player_speed
                player_pos[1] += math.sin(player_angle - math.pi/2) * player_speed
            elif event.key == pygame.K_d:
                player_pos[0] += math.cos(player_angle + math.pi/2) * player_speed
                player_pos[1] += math.sin(player_angle + math.pi/2) * player_speed
            # Handle rotation keys
            elif event.key == pygame.K_LEFT:
                player_angle -= math.pi / 180 * 5  # Rotate left
            elif event.key == pygame.K_RIGHT:
                player_angle += math.pi / 180 * 5  # Rotate right

    # Calculate the player's direction vector based on the angle
    player_dir = [math.cos(player_angle), math.sin(player_angle)]

    # Draw the player
    screen.fill((255, 255, 255))
    pygame.draw.circle(screen, (255, 0, 0), player_pos, 10)
    pygame.draw.line(screen, (255, 0, 0), player_pos, (player_pos[0] + player_dir[0] * 20, player_pos[1] + player_dir[1] * 20), 2)

    # Update the screen
    pygame.display.flip()
