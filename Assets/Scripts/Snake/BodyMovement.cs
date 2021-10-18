using System.Collections.Generic;
using UnityEngine;
using Dreamteck.Splines;

public sealed class BodyMovement
{
    #region Parameters
    private readonly int gapBetweenBody;
    private readonly Transform head = null;
    private readonly MeshRenderer headMeshRenderer = null;
    private readonly SplineFollower follower = null;

    private readonly List<GameObject> bodyParts = null;
    private readonly List<Vector3> positionsHistory = null;

    private const int minPositionInHistory = 0;

    private IHeadMovement headMovement = null;
    private HeadState headState;

    public List<Vector3> PositionsHistory => positionsHistory;


    public enum HeadState
    {
        Controllable,
        Uncontrollable
    }

    public HeadState State { get => headState; set => headState = value; }

    public IHeadMovement HeadMovement { get => headMovement; set => headMovement = value; }
    #endregion

    public BodyMovement(Transform head, SplineFollower follower, MeshRenderer headMeshRenderer, LayerMask ground, float lateralSpeed, float raycastMaxDistance, int gapBetweenBody)
    {
        bodyParts = new List<GameObject>();
        positionsHistory = new List<Vector3>();

        headState = HeadState.Controllable;
        headMovement = new ControllableHead(positionsHistory, head, follower, ground, lateralSpeed, raycastMaxDistance);

        this.head = head;
        this.follower = follower;
        this.headMeshRenderer = headMeshRenderer;
        this.gapBetweenBody = gapBetweenBody;
    }

    #region Custom methods
    public void MakeMove()
    {
        headMovement.HeadMovement();
        TailMovement();
    }

    public void GrowSnake(GameObject tail)
    {
        GameObject lastObject = bodyParts.Count > 0 ? bodyParts[bodyParts.Count - 1] : head.gameObject;

        GameObject newBody = Object.Instantiate(tail, lastObject.transform.position, lastObject.transform.rotation);

        if (newBody.TryGetComponent(out MeshRenderer meshRenderer))
        {
            meshRenderer.material.color = headMeshRenderer.material.color;
        }

        bodyParts.Add(newBody);
    }

    private void TailMovement()
    {
        int index = 0;

        foreach (GameObject body in bodyParts)
        {
            int penultimatePositionInHistory = positionsHistory.Count - 1;

            Vector3 point = positionsHistory[Mathf.Clamp(index * gapBetweenBody, minPositionInHistory, penultimatePositionInHistory)];
            Vector3 moveDirection = point - body.transform.position;

            body.transform.position += follower.followSpeed * Time.deltaTime * moveDirection;
            body.transform.LookAt(point);

            index++;
        }
    }
    #endregion
}
