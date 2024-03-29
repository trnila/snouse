#!/usr/bin/env python3
import pygame

pygame.init()
screen = pygame.display.set_mode((0, 0), pygame.FULLSCREEN)
clock = pygame.time.Clock()

font = pygame.font.SysFont(None, int(screen.get_height() * 0.05))
texts = ["Hold mouse to record", "delete or backspace to start over", "Esc or q to stop"]
text_surfaces = []
for text in texts:
    text_surfaces.append(font.render(text, True, (255, 255, 255)))

running = True
prev_pos = (0, 0)
first_point = True
points = []
rel_points = []
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        elif event.type == pygame.MOUSEMOTION and pygame.mouse.get_pressed()[0]:
            if first_point:
                first_point = False
            else:
                rel_points.append((prev_pos[0] - event.pos[0], prev_pos[1] - event.pos[1]))
                points.append(event.pos)
            prev_pos = event.pos
        elif event.type == pygame.KEYDOWN:
            if event.key in (pygame.K_q, pygame.K_ESCAPE):
                running = False
            elif event.key in (pygame.K_DELETE, pygame.K_BACKSPACE):
                points = []
                rel_points = []

    screen.fill((0, 0, 0))

    for point in points:
        pygame.draw.circle(screen, (255, 255, 255), point, 1)

    y = 0
    for text_surface in text_surfaces:
        screen.blit(text_surface, (0, y))
        y += text_surface.get_height()
    pygame.display.flip()
    clock.tick(60)

pygame.quit()

with open("src/trajectory.h", "w") as f:
    f.write("static const uint32_t trajectory_delay_ms = 17;\n")
    f.write("static const int8_t trajectory[][2] = {")
    for a, b in rel_points:
        f.write(f"{{{-a}, {-b}}}, ")
    f.write("};")
