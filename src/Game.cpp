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


    Vector2 temp1 = {(float)GetRandomValue(2*CELL_SIZE, 38*CELL_SIZE),
        (float)GetRandomValue(21* CELL_SIZE, 80 * CELL_SIZE)};
    Vector2 temp2 = {(float)GetRandomValue(2*CELL_SIZE, 38*CELL_SIZE),
        (float)GetRandomValue(21* CELL_SIZE, 80 * CELL_SIZE)};
    Vector2 temp3 = {(float)GetRandomValue(2*CELL_SIZE, 38*CELL_SIZE),
        (float)GetRandomValue(21* CELL_SIZE, 80 * CELL_SIZE)};
    StageLayout* first_stage = new StageLayout(temp1);
    StageLayout* second_stage = new StageLayout(temp2);
    StageLayout* third_stage = new StageLayout(temp3);
    m_Window->RegisterStates(first_stage, second_stage, third_stage);
    m_Candies = { new PickupItem(first_stage->CandyPosition),
                  new PickupItem(second_stage->CandyPosition),
                  new PickupItem(third_stage->CandyPosition)};
    m_PickedCandies = {};
    m_CandiesPositions = {temp1, temp2, temp3};
}

void Game::Run()
{

    std::vector<Shader> const shaders = {
        LoadShader(nullptr, "resources/shaders/pp_original.glsl"),
        LoadShader(nullptr, "resources/shaders/pp_harsh.glsl"),
        LoadShader(nullptr, "resources/shaders/pp_gray.glsl")
    };

    Image const menuImage = LoadImage("resources/images/main_screen.png");
    Texture2D const menuTexture = LoadTextureFromImage(menuImage);
    Image const winImage = LoadImage("resources/images/win_screen.png");
    Texture2D const winTexture = LoadTextureFromImage(winImage);
    Image const loseImage = LoadImage("resources/images/lose_screen.png");
    Texture2D const loseTexture = LoadTextureFromImage(loseImage);
    Image const creditsImage = LoadImage("resources/images/credits_screen.png");
    Texture2D const creditsTexture = LoadTextureFromImage(creditsImage);

    while(!WindowShouldClose())
    {

        if (IsKeyPressed(KEY_RIGHT_BRACKET)) currentColorScheme++;
        else if (IsKeyPressed(KEY_LEFT_BRACKET)) currentColorScheme--;
        if (currentColorScheme >= 3) currentColorScheme = 0;
        else if (currentColorScheme < 0) currentColorScheme = 3 - 1;

#ifdef NJ_DEBUG
        if (IsKeyPressed(KEY_ONE))
        {
                       m_CurrState = GAME_STATE::WIN;
        }
        else if (IsKeyPressed(KEY_TWO))
        {
                       m_CurrState = GAME_STATE::LOSE;
        }
        else if (IsKeyPressed(KEY_THREE))
        {
                       m_CurrState = GAME_STATE::CREDITS;
        }
        else if (IsKeyPressed(KEY_FOUR))
        {
                       m_CurrState = GAME_STATE::MENU;
        }
#endif

        BeginDrawing();
        BeginShaderMode(shaders[currentColorScheme]);
        ClearBackground(LIGHT_COLORS[currentColorScheme]);

        switch (m_CurrState)
        {
            case GAME_STATE::MENU:
                DrawTextureEx(menuTexture, {0, 0}, 0, CELL_SIZE, WHITE);
                if (IsKeyPressed(KEY_V))
                {
                    Reset();
                    m_CurrState = GAME_STATE::GAME;
                }
                else if (IsKeyPressed(KEY_C))
                {
                    m_CurrState = GAME_STATE::CREDITS;
                }
                break;
            case GAME_STATE::GAME:
                if (!m_Player->CheckLoss())
                {
                    if (IsKeyPressed(KEY_RIGHT_BRACKET)) currentColorScheme++;
                    else if (IsKeyPressed(KEY_LEFT_BRACKET)) currentColorScheme--;
                    if (currentColorScheme >= 3) currentColorScheme = 0;
                    else if (currentColorScheme < 0) currentColorScheme = 3 - 1;
                if(TimerDone(m_Timer) && m_WitchWasLookingLastFrame)
                {
                    m_Witch->TurnAround();
                    SetTimer(m_Timer, (float)GetRandomValue(3, 10));
                    m_WitchWasLookingLastFrame = false;
                    m_AnimationFrameCounter = 0;
                }
                else if(TimerDone(m_Timer) && !m_WitchWasLookingLastFrame)
                {
                    ++m_AnimationFrameCounter;
                    if(m_AnimationFrameCounter == 16)
                        m_WitchWasLookingLastFrame = true;
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
                    bool player_touches_candy = {
                        m_Player->GetPosition().x >= m_CandiesPositions[m_CurrentStage].x - 1*CELL_SIZE &&
                        m_Player->GetPosition().x <= m_CandiesPositions[m_CurrentStage].x + 6*CELL_SIZE + 1*CELL_SIZE &&
                        m_Player->GetPosition().y >= m_CandiesPositions[m_CurrentStage].y - 6*CELL_SIZE - 1*CELL_SIZE &&
                        m_Player->GetPosition().y <= m_CandiesPositions[m_CurrentStage].y + 1*CELL_SIZE
                    };
                    if(player_touches_candy && !m_PickedCandies.contains(m_Candies[m_CurrentStage]))
                        m_PickedCandies.insert(m_Candies[m_CurrentStage]);

                    if(m_PickedCandies.size() == 3 && m_Player->IsTop() && m_CurrentStage == 2)
                        m_CurrState = GAME_STATE::WIN;

                    UpdateTimer(m_Timer);
                    m_Player->Draw();
                    if(m_AnimationFrameCounter <= 0 || m_AnimationFrameCounter > 200)
                        m_Witch->Draw();
                    else
                        m_Witch->Animate();

                    if(!m_PickedCandies.contains(m_Candies[m_CurrentStage]))
                        m_Candies[m_CurrentStage]->Draw();
                    DrawText(TextFormat("Current Stage: %i", m_CurrentStage), 120, 300, 25, DARK_COLORS[currentColorScheme]);



        }
        else
        {
            m_CurrState = GAME_STATE::LOSE;
        }
        break;
        case GAME_STATE::LOSE:
            DrawTextureEx(loseTexture, { 0, 0 }, 0, CELL_SIZE, WHITE);
            if (IsKeyPressed(KEY_R))
            {
                m_CurrState = GAME_STATE::GAME;
                Reset();
                m_PickedCandies.clear();
                m_CurrentStage = 0;
            }
            break;
        case GAME_STATE::WIN:
        DrawTextureEx(winTexture, { 0, 0 }, 0, CELL_SIZE, WHITE);
            if (IsKeyPressed(KEY_R))
            {
                m_CurrState = GAME_STATE::GAME;
                Reset();
                m_PickedCandies.clear();
                m_CurrentStage = 0;
            }
            if(IsKeyPressed(KEY_M))
                m_CurrState = GAME_STATE::MENU;
            if(IsKeyPressed(KEY_C))
                m_CurrState = GAME_STATE::CREDITS;
            break;
        case GAME_STATE::CREDITS:
            DrawTextureEx(creditsTexture, {0, 0}, 0, CELL_SIZE, WHITE);
            if (IsKeyPressed(KEY_M))
            {
                m_CurrState = GAME_STATE::MENU;
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

void Game::Reset()
{
    m_Player->Reset();
    m_Witch->Reset();
    m_CurrentStage = 0;
    m_PlayerIsBottom = false;
    m_PlayerIsTop = false;
    Vector2 temp1 = {(float)GetRandomValue(2*CELL_SIZE, 38*CELL_SIZE),
        (float)GetRandomValue(21* CELL_SIZE, 80 * CELL_SIZE)};
    Vector2 temp2 = {(float)GetRandomValue(2*CELL_SIZE, 38*CELL_SIZE),
        (float)GetRandomValue(21* CELL_SIZE, 80 * CELL_SIZE)};
    Vector2 temp3 = {(float)GetRandomValue(2*CELL_SIZE, 38*CELL_SIZE),
        (float)GetRandomValue(21* CELL_SIZE, 80 * CELL_SIZE)};
    StageLayout* first_stage = new StageLayout(temp1);
    StageLayout* second_stage = new StageLayout(temp2);
    StageLayout* third_stage = new StageLayout(temp3);
    m_Window->RegisterStates(first_stage, second_stage, third_stage);
    m_Candies = { new PickupItem(first_stage->CandyPosition),
                  new PickupItem(second_stage->CandyPosition),
                  new PickupItem(third_stage->CandyPosition) };
    m_PickedCandies = {};
    m_CandiesPositions = { temp1, temp2, temp3 };
}