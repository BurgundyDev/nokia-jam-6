//
// Created by zysko on 25.02.2024.
//

#include "Game.h"

#include <nokia-jam-six.h>

Game::Game() : m_CurrState(GAME_STATE::MENU)
{
    m_Timer = new Timer();
    m_Witch = new Witch();
#ifndef NOKIA_BUILD
    m_Player = new Player(m_PlayerIsTop, m_PlayerIsBottom, CELL_SIZE*CELL_COUNT_WIDTH - 50, CELL_SIZE*CELL_COUNT_HEIGHT - 80);
#endif
#ifdef NOKIA_BUILD
    m_Player = new Player(m_PlayerIsTop, m_PlayerIsBottom, CELL_SIZE*CELL_COUNT_WIDTH - 5, CELL_SIZE*CELL_COUNT_HEIGHT - 8);
#endif
    m_Window = new Window();
    SetTimer(m_Timer, (float)GetRandomValue(1, 10));
    m_PlayerIsBottom = false;
    m_PlayerIsTop = false;
    m_CurrentStage = 0;
}

void Game::Run()
{

    std::vector<Shader> const shaders = {
        LoadShader(nullptr, "resources/shaders/pp_original.glsl"),
        LoadShader(nullptr, "resources/shaders/pp_harsh.glsl"),
        LoadShader(nullptr, "resources/shaders/pp_gray.glsl")
    };


    while(!WindowShouldClose())
    {

        if (IsKeyPressed(KEY_RIGHT_BRACKET)) currentColorScheme++;
        else if (IsKeyPressed(KEY_LEFT_BRACKET)) currentColorScheme--;
        if (currentColorScheme >= 3) currentColorScheme = 0;
        else if (currentColorScheme < 0) currentColorScheme = 3 - 1;

        BeginDrawing();
        BeginShaderMode(shaders[currentColorScheme]);
        ClearBackground(LIGHT_COLORS[currentColorScheme]);

        switch (m_CurrState)
    {
    case GAME_STATE::MENU:
        DrawText("Press Enter to start", 10, 10, 20, DARK_COLORS[currentColorScheme]);
        if (IsKeyPressed(KEY_ENTER))
        {
            m_CurrState = GAME_STATE::GAME;
        }
        break;
    case GAME_STATE::GAME:

        if (!m_Player->CheckLoss())
        {
            if (IsKeyPressed(KEY_RIGHT_BRACKET)) currentColorScheme++;
            else if (IsKeyPressed(KEY_LEFT_BRACKET)) currentColorScheme--;
            if (currentColorScheme >= 3) currentColorScheme = 0;
            else if (currentColorScheme < 0) currentColorScheme = 3 - 1;

            if(TimerDone(m_Timer))
            {
                m_Witch->TurnAround();
                SetTimer(m_Timer, (float)GetRandomValue(3, 10));
            }
            if(m_Player->IsTop() && m_CurrentStage < 2)
            {
                m_Window->StageUp();
                m_Player->SetTop(false);
                ++m_CurrentStage;
                m_Player->SetPosition(m_Player->GetPosition().x, CELL_SIZE*CELL_COUNT_HEIGHT - 80);

            }
            if(m_Player->IsBottom() && m_CurrentStage > 0)
            {
                m_Window->StageDown();
                m_Player->SetBottom(false);
                --m_CurrentStage;
                m_Player->SetPosition(m_Player->GetPosition().x, (19*CELL_SIZE));
            };
            m_Player->Update(m_Witch->CheckState());
            UpdateTimer(m_Timer);
            m_Player->Draw();
            m_Witch->Draw();
            DrawText(TextFormat("Current Stage: %i", m_CurrentStage), 120, 300, 25, DARK_COLORS[currentColorScheme]);
        }
        else
        {
            m_CurrState = GAME_STATE::LOSE;
        }
        break;
    case GAME_STATE::LOSE:
        DrawText("You lost! Press Enter to restart", 10, 10, 20, DARK_COLORS[currentColorScheme]);
        if (IsKeyPressed(KEY_ENTER))
        {
            m_CurrState = GAME_STATE::GAME;
            m_Player->Reset();
            m_Witch->Reset();
        }
        break;
    case GAME_STATE::WIN:
        DrawText("You won! Press Enter to restart", 10, 10, 20, DARK_COLORS[currentColorScheme]);
        if (IsKeyPressed(KEY_ENTER))
        {
            m_CurrState = GAME_STATE::GAME;
            m_Player->Reset();
            m_Witch->Reset();
        }
        break;
    }
        EndShaderMode();
        EndDrawing();
    }
}


void Game::Draw()
{
}

void Game::Setup()
{
}
