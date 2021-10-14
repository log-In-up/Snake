using UnityEngine;
using Dreamteck.Splines;

[DisallowMultipleComponent]
[RequireComponent(typeof(SplineFollower))]
public sealed class SnakeBehaviour : MonoBehaviour
{
    #region Parameters
    [SerializeField] private TagProvider tagProvider = null;
    [SerializeField, Min(0.0f)] private float lateralMovementSpeed = 1.0f;
    [SerializeField, Min(0.0f)] private float raycastMaxDistance = 100.0f;
    [SerializeField, Min(0)] private int gap = 10;
    [SerializeField] private LayerMask ground;
    [SerializeField] private GameObject bodyPrefab = null;

    private SplineFollower splineFollower = null;
    private BodyMovement body = null;
    private SnakeTriggerBehaviour snakeTriggerBehaviour = null;
    #endregion

    #region MonoBehaviour API
    private void Awake()
    {
        splineFollower = GetComponent<SplineFollower>();
    }

    private void Start()
    {
        body = new BodyMovement(transform, splineFollower, lateralMovementSpeed, raycastMaxDistance, gap, ground);
        snakeTriggerBehaviour = new SnakeTriggerBehaviour();

        body.GrowSnake(bodyPrefab);
    }

    private void Update()
    {
        body.MakeMove();
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.CompareTag(tagProvider.FoodTag))
        {
            body.GrowSnake(bodyPrefab);
        }

        if (other.CompareTag(tagProvider.CrystalTag))
        {
            snakeTriggerBehaviour.WhenEatingCrystal();
        }

        if (other.CompareTag(tagProvider.ObstacleTag))
        {
            snakeTriggerBehaviour.WhenEatingObstacle();
        }
    }
    #endregion
}
