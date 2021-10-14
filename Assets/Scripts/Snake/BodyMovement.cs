using System.Collections.Generic;
using UnityEngine;
using Dreamteck.Splines;

sealed class BodyMovement
{
    #region Parameters
    private readonly float lateralSpeed, raycastMaxDistance;
    private readonly int gapBetweenBody;
    private readonly Transform head = null;
    private readonly LayerMask ground;

    private readonly List<GameObject> bodyParts = null;
    private readonly List<Vector3> positionsHistory = null;

    private readonly SplineFollower follower = null;

    private const int minPositionInHistory = 0, firstPositionInHistory = 0, leftMouseButton = 0, firstTouch = 0;
    private const float middleOfViewport = 0.5f, moveToLeft = -1.0f, moveToRight = 1.0f;

    private float inputValue;
    #endregion

    public BodyMovement(Transform head, SplineFollower follower, float lateralSpeed, float raycastMaxDistance, int gapBetweenBody, LayerMask ground)
    {
        bodyParts = new List<GameObject>();
        positionsHistory = new List<Vector3>();

        this.head = head;
        this.lateralSpeed = lateralSpeed;
        this.raycastMaxDistance = raycastMaxDistance;
        this.follower = follower;
        this.gapBetweenBody = gapBetweenBody;
        this.ground = ground;
    }

    #region Custom methods
    public void MakeMove()
    {
        HeadMovement();
        TailMovement();
    }

    public void GrowSnake(GameObject tail)
    {
        GameObject newBody = Object.Instantiate(tail);
        bodyParts.Add(newBody);
    }

    private void HeadMovement()
    {
        inputValue = 0;

        if (Input.touchCount > 0)
        {
            TouchInput();
        }
        else if (Input.GetMouseButton(leftMouseButton))
        {
            MouseInput();
        }

        float blendValue = follower.offsetModifier.blend + inputValue;

        follower.offsetModifier.blend = Mathf.Clamp01(blendValue);

        positionsHistory.Insert(firstPositionInHistory, head.position);
    }

    private void MouseInput()
    {
        Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);

        SetInputValue(ray);
    }

    private void SetInputValue(Ray ray)
    {
        if (Physics.Raycast(ray, out RaycastHit hitInfo, raycastMaxDistance, ground.value))
        {
            if (head.position.z < hitInfo.point.z)
            {
                inputValue = moveToLeft * Time.deltaTime * lateralSpeed;
            }
            else if (head.position.z > hitInfo.point.z)
            {
                inputValue = moveToRight * Time.deltaTime * lateralSpeed;
            }
        }
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

    private void TouchInput()
    {
        Touch touch = Input.GetTouch(firstTouch);

        Ray ray = Camera.main.ScreenPointToRay(touch.position);

        SetInputValue(ray);
    }
    #endregion
}
