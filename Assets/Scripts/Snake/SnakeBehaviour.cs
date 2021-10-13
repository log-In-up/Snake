using UnityEngine;
using Dreamteck.Splines;

[DisallowMultipleComponent]
[RequireComponent(typeof(SplineFollower))]
public sealed class SnakeBehaviour : MonoBehaviour
{
    [SerializeField, Min(0.0f)] private float lateralMovementSpeed = 1.0f;
    [SerializeField, Min(0)] private int gap = 10;
    [SerializeField] private GameObject bodyPrefab = null;
    [SerializeField] private JoystickController joystickController = null;

    private SplineFollower splineFollower = null;
    private BodyMovement body = null;

    private void Awake()
    {
        splineFollower = GetComponent<SplineFollower>();
    }

    private void Start()
    {
        body = new BodyMovement(bodyPrefab, transform, splineFollower, joystickController, lateralMovementSpeed, gap);

        body.GrowSnake();
    }

    private void Update()
    {
        body.MakeMove();
    }
}
