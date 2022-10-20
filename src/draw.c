void draw_rays(t_settings *data)
{
	int x1;
	int y1;
	int ray_y;
	int ray_x;
	int dx;
	int dy;
	double angle;
	float y_offset;
	float x_offset;

	// for(int i = 0; i < FOV; i += 1)
	// {
	// 	angle = data->angle + (FOV / 2 - i) * RAD;
	// 	draw_line(data, angle, 600, 0x00AAFF00);
	// }
	int nextY;
	int nextX;
	int x_off;
	int y_off;
	double rad;
	int ray_length_y;
	int ray_length_x;
	int deltaX;
	int deltaY;
	// horizontal
	// if (0.5 * PI < data->angle && data->angle < 1.5 * PI)
	// {
	// 	printf("-----------------------\n");
	// 	printf("angle = %f\n", data->angle);
	// 	nextY = (int)data->posY / (screenHeight / mapHeight) * (screenHeight / mapHeight);
	// 	printf("nextY = %d\n", nextY);
	// 	rad = data->angle - PI;
	// 	printf("rad = %f\ndeltaY = %d\n", rad,abs((int)data->posY - nextY));
	// 	nextX = data->posX - tan(rad) * abs((int)data->posY - nextY);
	// 	printf("nextX = %d\n", nextX);
	// 	for(int i = 0; i < 360; i += 1)
	// 	{
	// 		for (int r = 0; r < 4; r++)
	// 		{
	// 			x1 = r * cos(i * PI / 180);
	// 			y1 = r * sin(i * PI / 180);
	// 			my_mlx_pixel_put(&data->img, nextX + x1, nextY + y1, 0x00658354);
	// 		}
	// 	}
	// }
	for(int i = 0; i < FOV; i += 1)
	{
		angle = data->angle + (FOV / 2 - i) * RAD;
		for (int z = 0; z < mapHeight; z += 1)
		{
			if (0.5 * PI < angle && angle < 1.5 * PI)
			{
				nextY = ((int)data->posY / (screenHeight / mapHeight) - z) * (screenHeight / mapHeight);
				rad = angle - PI;
				nextX = data->posX - tan(rad) * abs((int)data->posY - nextY);
			}
			else
			{
				nextY = ((int)data->posY / (screenHeight / mapHeight) + z + 1) * (screenHeight / mapHeight);
				rad = angle;
				nextX = data->posX + tan(rad) * abs((int)data->posY - nextY);
			}
			deltaX = abs((int)data->posX - nextX); 
			deltaY = abs((int)data->posY - nextY);
			ray_length_y = sqrt(deltaX * deltaX + deltaY * deltaY);
			if (worldMap[nextY / 26][nextX / 26] != 0)
				break ;
		}
		draw_line(data, angle, ray_length_y, 0x00FF0000);
	}
	// for(int i = 0; i < FOV; i += 1)
	// {
		// angle = data->angle + (FOV / 2 - i) * RAD;
		// angle = data->angle;
		// for (int z = 0; z < mapHeight; z += 1)
		// {
		// 	if (angle > PI)
		// 	{
		// 		nextX = ((int)data->posY / (screenHeight / mapHeight) - z) * (screenHeight / mapHeight);
		// 		rad = 2 * PI - angle;
		// 		nextY = data->posY + abs((int)data->posX - nextX) / tan(rad);
		// 		draw_point(data, nextX, nextY);
		// 	}
		// 	else
		// 	{
		// 		nextX = ((int)data->posY / (screenHeight / mapHeight) + z + 1) * (screenHeight / mapHeight);
		// 		rad = angle;
		// 		nextY = data->posY + abs((int)data->posX - nextX) / tan(rad);
		// 		draw_point(data, nextX, nextY);
		// 	}
		// 	// deltaX = abs((int)data->posX - nextX); 
		// 	// deltaY = abs((int)data->posY - nextY);
		// 	// ray_length_x = sqrt(deltaX * deltaX + deltaY * deltaY);
		// 	// if (worldMap[nextY / 26][nextX / 26] != 0)
		// 	// {
		// 	// 	printf("hhitt!!!!\n");
		// 	// 	break ;
		// 	// }
		// }
			// int wall = worldMap[nextY / 26][nextX / 26]
			// printf("")
		// draw_line(data, angle, ray_length_x, 0x00FF0000);
		// draw_line(data, angle, ray_length_y, 0x00FF0000);
		// draw_point(data, 189, 208);
	// }
}