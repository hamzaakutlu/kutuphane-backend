import { NestFactory } from '@nestjs/core';
import { AppModule } from './app.module';

async function bootstrap() {
  const app = await NestFactory.create(AppModule);
    app.enableCors();
  // Portu 3001 yapıyoruz
    await app.listen(3004);
}
bootstrap();