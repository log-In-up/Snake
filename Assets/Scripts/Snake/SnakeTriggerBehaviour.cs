using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public sealed class SnakeTriggerBehaviour
{
    #region Parameters
    private readonly MeshRenderer snakeMeshRenderer = null;
    private readonly GameManager gameManager = null;
    #endregion

    public SnakeTriggerBehaviour(MeshRenderer snakeMeshRenderer, GameManager gameManager)
    {
        this.snakeMeshRenderer = snakeMeshRenderer;
        this.gameManager = gameManager;
    }

    #region Custom methods
    public void OnTriggerWithFood(Collider collider)
    {
        if (collider.TryGetComponent(out MeshRenderer meshRenderer))
        {
            if (meshRenderer.material.color == snakeMeshRenderer.material.color)
            {
                Object.Destroy(collider.gameObject);
                gameManager.FoodCount++;
            }
            else
            {
                gameManager.LevelFailed.Invoke();
            }
        }
    }

    public void OnTriggerWithObstacle(Collider collider, BodyMovement bodyMovement)
    {
        if (bodyMovement.State == BodyMovement.HeadState.Uncontrollable)
        {
            Object.Destroy(collider.gameObject);
        }
        else
        {
            gameManager.LevelFailed.Invoke();
        }
    }
    #endregion
}
