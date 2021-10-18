using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Dreamteck.Splines;

public sealed class ControllableHead : IHeadMovement
{
    private readonly float lateralSpeed, raycastMaxDistance;
    private readonly LayerMask ground;

    private readonly SplineFollower follower = null;
    private readonly Transform head = null;

    private readonly List<Vector3> positionsHistory = null;

    private const float moveToLeft = -1.0f, moveToRight = 1.0f;
    private const int firstPositionInHistory = 0, leftMouseButton = 0, firstTouch = 0;

    private float inputValue;

    public ControllableHead(List<Vector3> positionsHistory, Transform head, SplineFollower splineFollower, LayerMask ground, float lateralSpeed, float raycastMaxDistance)
    {
        this.positionsHistory = positionsHistory;

        follower = splineFollower;
        this.head = head;
        this.ground = ground;
        this.lateralSpeed = lateralSpeed;
        this.raycastMaxDistance = raycastMaxDistance;
    }

    public void HeadMovement()
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

    private void TouchInput()
    {
        Touch touch = Input.GetTouch(firstTouch);

        Ray ray = Camera.main.ScreenPointToRay(touch.position);

        SetInputValue(ray);
    }
}
