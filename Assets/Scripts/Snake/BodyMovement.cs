using System.Collections.Generic;
using UnityEngine;
using Dreamteck.Splines;

public sealed class BodyMovement
{
    private readonly float lateralSpeed;
    private readonly int gapBetweenBody;
    private readonly Transform head = null;
    private readonly GameObject tail = null;

    private readonly List<GameObject> bodyParts = null;
    private readonly List<Vector3> positionsHistory = null;

    private readonly SplineFollower follower = null;
    private readonly JoystickController controller = null;

    private const int minPositionInHistory = 0, firstPositionInHistory = 0;

    public BodyMovement(GameObject tail, Transform head, SplineFollower follower, JoystickController controller, float lateralSpeed, int gapBetweenBody)
    {
        bodyParts = new List<GameObject>();
        positionsHistory = new List<Vector3>();

        this.head = head;
        this.tail = tail;
        this.controller = controller;
        this.lateralSpeed = lateralSpeed;
        this.follower = follower;
        this.gapBetweenBody = gapBetweenBody;
    }

    public void MakeMove()
    {
        HeadMovement();
        TailMovement();
    }

    public void GrowSnake()
    {
        GameObject newBody = Object.Instantiate(tail);
        bodyParts.Add(newBody);
    }

    private void HeadMovement()
    {
        float blendValue = follower.offsetModifier.blend + (controller.Horizontal() * Time.deltaTime * lateralSpeed);

        follower.offsetModifier.blend = Mathf.Clamp(blendValue, 0.0f, 1.0f);

        positionsHistory.Insert(firstPositionInHistory, head.position);
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
}
