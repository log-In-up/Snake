using UnityEngine;
using Dreamteck.Splines;
using System.Collections;
using DG.Tweening;
using System;

[DisallowMultipleComponent]
[RequireComponent(typeof(SplineFollower), typeof(MeshRenderer))]
public sealed class SnakeBehaviour : MonoBehaviour
{
    #region Parameters
    [Header("Movement settings")]
    [SerializeField, Min(0.0f)] private float lateralMovementSpeed = 1.0f;
    [SerializeField, Min(0.0f)] private float raycastMaxDistance = 100.0f;
    [SerializeField, Min(0)] private int gap = 10;
    [SerializeField] private LayerMask ground;

    [Header("Fever settings")]
    [SerializeField, Min(0.0f)] private float feverMovementMultiplyer = 3.0f;
    [SerializeField, Min(0.0f)] private float feverDuration = 5.0f;
    [SerializeField, Min(0.0f)] private float alignToMiddleTime = 2.0f;
    [SerializeField, Min(0)] private int requiredCrystalsForFever = 4;

    [Header("Components")]
    [SerializeField] private GameManager gameManager = null;
    [SerializeField] private TagProvider tagProvider = null;
    [SerializeField] private GameObject bodyPrefab = null;

    private SplineFollower splineFollower = null;
    private MeshRenderer thisMeshRenderer = null;
    private Coroutine fever = null;

    private BodyMovement body = null;
    private SnakeTriggerBehaviour triggerBehaviour = null;

    private const float middlePosition = 0.5f;

    private int absorbedCrystals;
    #endregion

    #region MonoBehaviour API
    private void Awake()
    {
        splineFollower = GetComponent<SplineFollower>();
        thisMeshRenderer = GetComponent<MeshRenderer>();
    }

    private void Start()
    {
        body = new BodyMovement(transform, splineFollower, thisMeshRenderer, ground, lateralMovementSpeed, raycastMaxDistance, gap);
        triggerBehaviour = new SnakeTriggerBehaviour(thisMeshRenderer, gameManager);

        absorbedCrystals = 0;

        body.GrowSnake(bodyPrefab);
    }

    private void Update()
    {
        body.MakeMove();
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.CompareTag(tagProvider.CrystalTag))
        {
            OnTriggerWithCrystal(other);
        }

        if (other.CompareTag(tagProvider.FoodTag))
        {
            triggerBehaviour.OnTriggerWithFood(other);

            body.GrowSnake(bodyPrefab);
        }

        if (other.CompareTag(tagProvider.ObstacleTag))
        {
            triggerBehaviour.OnTriggerWithObstacle(other, body);
        }
    }
    #endregion

    #region Custom methods
    private void OnTriggerWithCrystal(Collider collider)
    {
        Destroy(collider.gameObject);

        gameManager.CrystalsCount++;
        absorbedCrystals++;

        if (absorbedCrystals >= requiredCrystalsForFever)
        {
            body.HeadMovement = SwitchState(BodyMovement.HeadState.Uncontrollable);

            DOTween.To(() => splineFollower.offsetModifier.blend, x => splineFollower.offsetModifier.blend = x, middlePosition, alignToMiddleTime)
                .OnComplete(OnPickingUpAllCrystals);

            absorbedCrystals = 0;
        }
    }

    private void OnPickingUpAllCrystals()
    {
        splineFollower.followSpeed *= feverMovementMultiplyer;

        if(Camera.main.TryGetComponent(out SplineFollower cameraFollower))
        {
            cameraFollower.followSpeed *= feverMovementMultiplyer;
        }

        if (fever != null)
        {
            StopCoroutine(fever);
        }
        fever = StartCoroutine(Fever(feverDuration));
    }

    private IEnumerator Fever(float feverDuration)
    {
        yield return new WaitForSeconds(feverDuration);

        splineFollower.followSpeed /= feverMovementMultiplyer;

        if (Camera.main.TryGetComponent(out SplineFollower cameraFollower))
        {
            cameraFollower.followSpeed /= feverMovementMultiplyer;
        }

        body.HeadMovement = SwitchState(BodyMovement.HeadState.Controllable);

        gameManager.CrystalsCount = 0;
    }

    public IHeadMovement SwitchState(BodyMovement.HeadState state)
    {
        body.State = state;

        body.HeadMovement = state switch
        {
            BodyMovement.HeadState.Controllable => new ControllableHead(body.PositionsHistory, transform, splineFollower, ground, lateralMovementSpeed, raycastMaxDistance),
            BodyMovement.HeadState.Uncontrollable => new UncontrollableHead(body.PositionsHistory, transform),
            _ => throw new NotImplementedException(),
        };

        return body.HeadMovement;
    }
    #endregion
}
